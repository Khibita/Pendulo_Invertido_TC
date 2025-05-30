#include "PIDControl.h"

PID_Discreto::PID_Discreto(float Kp, float Ki, float Kd, float dt)
    : Kp(Kp), Ki(Ki), Kd(Kd), dt(dt), integral(0.0f), prev_error(0.0f) {}

/**
 * @brief Calcula la señal de control PID discreto
 * @param setpoint Valor deseado/referencia
 * @param measured_value Valor medido/real
 * @return Señal de control calculada
 * 
 * Implementación básica de PID discreto con:
 * - Término Proporcional (P)
 * - Término Integral (I) con acumulación
 * - Término Derivativo (D) con diferencia finita
 */
float PID_Discreto::compute(float setpoint, float measured_value) {
    const float error = setpoint - measured_value;
    integral += error * dt;
    const float output = Kp * error + Ki * integral + Kd * (error - prev_error) / dt;
    prev_error = error;
    return output;
}

PID_IIR::PID_IIR(float Kp, float Ki, float Kd, float dt)
    : dt(dt) {
    const float inv_dt = 1.0f / dt;
    A0 = Kp + Ki * dt + Kd * inv_dt;
    A1 = -Kp - 2.0f * Kd * inv_dt;
    A2 = Kd * inv_dt;
    error[0] = error[1] = error[2] = 0.0f;
}

/**
 * @brief Calcula la señal de control PID en forma IIR
 * @param setpoint Valor deseado/referencia
 * @param measured_value Valor medido/real
 * @return Señal de control calculada
 * 
 * Implementación como filtro IIR (forma directa II) con:
 * - 3 coeficientes precalculados (A0, A1, A2)
 * - Historial de 3 errores pasados
 * - Más eficiente computacionalmente
 */
float PID_IIR::compute(float setpoint, float measured_value) {
    error[2] = error[1];
    error[1] = error[0];
    error[0] = setpoint - measured_value;
    return A0 * error[0] + A1 * error[1] + A2 * error[2];
}

PID_Filtrado::PID_Filtrado(float Kp, float Ki, float Kd, float dt, float N)
    : Kp(Kp), Ki(Ki), Kd(Kd), dt(dt), N(N),
      output(0.0f), d0(0.0f), d1(0.0f), fd0(0.0f), fd1(0.0f) {
    
    const float inv_dt = 1.0f / dt;
    A0 = Kp + Ki * dt;
    A1 = -Kp;

    A0d = Kd * inv_dt;
    A1d = -2.0f * Kd * inv_dt;
    A2d = Kd * inv_dt;

    const float tau = Kd / (Kp * N);
    const float alpha = dt / (2.0f * tau);
    alpha_1 = alpha / (alpha + 1.0f);
    alpha_2 = (alpha - 1.0f) / (alpha + 1.0f);

    error[0] = error[1] = error[2] = 0.0f;
}

/**
 * @brief Calcula la señal de control PID con derivada filtrada
 * @param setpoint Valor deseado/referencia
 * @param measured_value Valor medido/real
 * @return Señal de control calculada
 * 
 * Implementación con:
 * - Filtro pasa-bajos en término derivativo (factor N)
 * - Parte PI estándar
 * - Filtro de primer orden en término D
 * - Menos ruido en la acción derivativa
 */
float PID_Filtrado::compute(float setpoint, float measured_value) {
    error[2] = error[1];
    error[1] = error[0];
    error[0] = setpoint - measured_value;

    output += A0 * error[0] + A1 * error[1];

    d1 = d0;
    d0 = A0d * error[0] + A1d * error[1] + A2d * error[2];

    const float temp = fd0;
    fd0 = alpha_1 * (d0 + d1) - alpha_2 * fd1;
    fd1 = temp;

    return output + fd0;
}
