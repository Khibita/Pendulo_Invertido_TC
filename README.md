# 🧩 Proyecto: Péndulo Invertido

## 📋 Introducción
Este proyecto se centra en diseñar, construir y poner en marcha un péndulo invertido. Este es un sistema muy conocido en ingeniería de control porque es un ejemplo clásico de un sistema que no es lineal, es inestable y además tiene doble integración. 

El péndulo invertido presenta un desafío interesante, ya que hay que crear un sistema de control capaz de mantenerlo en equilibrio vertical desde cualquier posición inicial y frente a perturbaciones externas. Para lograrlo, se ha implementado un controlador PID usando un microcontrolador ESP32, apoyado por sensores de orientación como acelerómetro y giroscopio, y un sistema de actuadores con motores DC. 

Durante el desarrollo del proyecto, se han trabajado distintas áreas como:
- [ ] el diseño y fabricación del sistema mecánico con impresión 3D.
- [ ] la selección e integración de componentes electrónicos.
- [ ] la programación del controlador en el entorno Arduino y la sintonización del PID para validar el comportamiento del sistema.

Al final, se ha logrado crear un robot que puede mantenerse en posición vertical, resistir pequeñas perturbaciones y desplazarse controladamente. Todo el proceso está bien documentado y puedes consultarlo y reutilizarlo en este repositorio.

---

## 🎯 Objetivos
- [ ] Estabilidad en posición vertical (±5°)
- [ ] Compensación de empujones
- [ ] Arranque desde cualquier posición
- [ ] Implementación en ESP32
- [ ] Sintonización del PID

---

## 🛠️ Hardware
**Componentes usados:**
- [ ] ESP32: [WROOM 32D], elegimos está por su bajo costé, conexiones inalambricas y poder ejecutar codigo c.
- [ ] Sensor: [MPU9250], elegimos está por su bajo costé, y devolver aceleración en 9 ejes.
- [ ] Driver de motor: [TB6612FNG] se ajustaba a las caracteristicas necesarias
- [ ] Motores: [fz3176] Motor de corriente continua que se ajustaba al precio y potencia de consumo
- [ ] Batería: [ MN1604] Coloquialemente conocida de "petaca", produce 9V de alimentación, El sistema necesita más , conexión por cable, para siguie
- [ ] Regulador de Tensión: [LM7805]
- [ ] Condensador: [0.1uF y 0.2uf]
- [ ] Conectores entrada y salida :  3 de 2 pines.

-Recordar que tanto la conexión electrica , como la pcb se adjunta en este mismo repositorio.

---

## 🧱 Diseño mecánico
**Software de diseño usado:**  
- [ ] Para está pieza de geometría simple, pero que contaba con multiples caras, elegí freecad, debido que es con el estoy familiarizado por otras asignaturas y por tener entornos bien organizados y una comunidad activa. Aunque si es tu primera vez realizando este tipo de objetos con varias caras, te recomiendo aplicaciones con interfaces más modernas.

**Método de fabricación:**  
- [ ] Impresora 3D, en concreto la Anet A8. La impresión tardará bastante por culpa de los soportes, para reducir el tiempo, se podría probar o a inclinar la figura o rotar la figura para que el eje y quede como el eje x, precauición  son sujerencias no validadas. 

**Versiones del chasis y decisiones de diseño:**  
- [ ] Solo hay una versión, la publicada, en la cual prioricé que el centro de masas fuera lo más bajo posible y que estuviera centrado, apare de que no fuera necesario, tornillos más que para la placa base, aunque por como está  encastrada, no sería necesaría pasa su funcionamiento, recomiendo encarecidamente pornerlos.Para buscar un balance entre centro de masas bajo y porcentaje de ángulo de giro libre de las ruedas , sin que el chasis toque suelo, hice una incisio (diminuir el espesor a 1) en la parte baja del chasis un rectangulo para colocar la bateria , en caso de usar un portapilas más grande o una batería que superé las dimensiones de la usada habría que modificar el chasis.

---

## 🔌 Montaje
El montaje se divide en 2 partes:
- [ ] Soldar: soldar todos los componentes a la placa, en caso de querer reutilizar los componentes, recomiendo soldar conectores macho hembra a la placa en vez de los propios componentes. IMPORTANTE SEGUIR LAS DIRECCIONES DE LA PCB .
- [ ] Colocar las piezas: recomiendo empezar por la pcb una vez atornillada, seguir con los motores y por último pegar la batería con silicona al hueco posterior a la placa. 
---


## 📈 Control y software
**Controlador:** PID

**Implementación:**  
El lenguaje es .ino, compatible con  Esp32, pero las libreria en las que se basa, los pids a utilizar, está escrita en c++.

**Valores de cte del PID (Op 1 - reajustes pequeños en valores cercanos al (0,0), pero resistente a golpes fuertes):**  
- [ ] Kp = 50.0
- [ ] Ki = 1.0
- [ ] Kd = 20.0

**Valores de cte del PID (Op 1 - se mantiene quieto totalmente, pero sensible a golpes fuertes):**  
- [ ] Kp = 50.0
- [ ] Ki = 2.0
- [ ] Kd = 20.0

**PID Seleccionado**
- [ ] PID Filtrado, opción 3.


De forma resumida el codigo  compara el setpoint (posición destino) y la actual, a través del pid seleccionado, devuelve valores para los motores, que luego de ser normalizador , para enviar a los motores.

---

🎮 Control Inalambrico:

implementé la conexión por Bluetooth para que el sistema pudiera recibir órdenes en tiempo real desde un celular o una app, en mi caso serial terminal bluetooth, como si fuera un control remoto. Lo que hago es leer dos valores que llegan separados por una coma: uno controla el movimiento hacia adelante o atrás, y el otro el giro. Con esos datos, ajusto el setpoint del controlador PID para que el sistema se mueva según lo que el usuario indique, y también modifico la señal de los motores para que pueda girar fácilmente. Además, hice que el sistema mande de vuelta los valores recibidos por Bluetooth, así se puede ver desde el celular que la señal llegó bien y todo está funcionando como se espera.

---

## Resultados
**Hay que distingir dos casos según los valores de Kp, Ki, Kd elegidos:**
- [ ] Op 1:  El sistema llega conseguir estabilizarse en la mayoría de casos a golpes que incluso hagan tocar el suelo con el chasis. Una vez estabilizado empieza a tener pequeños sobre ajustes que hace que oscile un poco.
- [ ] Op 2:  El sistema consigue estabilizarse con golpes pequeños, pero en el caso de que el chasis toque suelo, no será capaz de conseguir levantarse de nuevo hasta chocar con algún objeto. Una vez estabilizado se mantiene estatico.

En resumen dependiendo de la respuestá deseada se puede elegir una u otra e incluso otras convinaciones de Kp, Ki y Kd. 

**Problemas con la Potencia**
- [ ] la conexión bluetooth hace que pierde algo de potencia los motores, por lo que es más sensible a perturbaciones, esto es debido a que el sistema no está pensado para una batería tan sencilla.
- [ ] Problemas de potencia, al romperseme los dos portapilas con que contaba tuve que hacer un arreglo con una batería de 9v auxiliar, por lo que se necesita conectar el robot a una fuente de energía. 

  
---
