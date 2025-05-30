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
- ESP32: [WROOM 32D], elegimos está por su bajo costé, conexiones inalambricas y poder ejecutar codigo c.
- Sensor: [MPU9250], elegimos está por su bajo costé, y devolver aceleración en 9 ejes.
- Driver de motor: [TB6612FNG] se ajustaba a las caracteristicas necesarias
- Motores: [fz3176] Motor de corriente continua que se ajustaba al precio y potencia de consumo
- Batería: [ MN1604] Coloquialemente conocida de "petaca", produce 9V de alimentación, El sistema necesita más , conexión por cable, para siguie
- Otros: [reguladores, cables, etc.]

_Recordar que tanto la conexión electrica , como la pcb se adjunta en este mismo repositorio.

---

## 🧱 Diseño mecánico
**Software de diseño usado:**  
_ Para está pieza de geometría simple, pero que contaba con multiples caras, elegí freecad, debido que es con el estoy familiarizado por otras asignaturas y por tener entornos bien organizados y una comunidad activa. Aunque si es tu primera vez realizando este tipo de objetos con varias caras, te recomiendo aplicaciones con interfaces más modernas.

**Método de fabricación:**  
_Impresora 3D, en concreto la Anet A8. La impresión tardará bastante por culpa de los soportes, para reducir el tiempo, se podría probar o a inclinar la figura o rotar la figura para que el eje y quede como el eje x, precauición  son sujerencias no validadas. 

**Versiones del chasis y decisiones de diseño:**  
_Solo hay una versión, la publicada, en la cual prioricé que el centro de masas fuera lo más bajo posible y que estuviera centrado, apare de que no fuera necesario, tornillos más que para la placa base, aunque por como está  encastrada, no sería necesaría pasa su funcionamiento, recomiendo encarecidamente pornerlos.Para buscar un balance entre centro de masas bajo y porcentaje de ángulo de giro libre de las ruedas , sin que el chasis toque suelo, hice una incisio (diminuir el espesor a 1) en la parte baja del chasis un rectangulo para colocar la bateria , en caso de usar un portapilas más grande o una batería que superé las dimensiones de la usada habría que modificar el chasis.

---

## 🔌 Montaje
_El montaje se divide en 2 partes:
- [ ] Soldar: soldar todos los componentes a la placa, en caso de querer reutilizar los componentes, recomiendo soldar conectores macho hembra a la placa en vez de los propios componentes. IMPORTANTE SEGUIR LAS DIRECCIONES DE LA PCB .
- [ ] Colocar las piezas: recomiendo empezar por la pcb, atornillarla una vez colocada, seguir con los motores y por último pegar la batería con silicona a su hueco. 
---


## 📈 Control y software
**Controlador:** PID

**Implementación:**  
_👉 [Lenguaje / IDE / Librerías utilizadas]_

**Sintonización del PID:**  
- Kp = ...
- Ki = ...
- Kd = ...

_👉 [Incluir código clave o referencia a archivos]_  
_👉 [Mención al uso de filtro complementario si aplica]_

---

## 🧪 Pruebas y resultados
**Escenarios de prueba:**
- Estabilidad
- Respuesta a perturbaciones
- Arranque desde diferentes posiciones

_👉 [Incluir fotos, vídeos o gráficas si hay]_

---

## 📎 Recursos y referencias
- [Enlace a datasheet de ESP32]
- [Tutorial uso MPU6050]
- [Página del driver TB6612FNG]
- [Otros recursos útiles]

---

## 🚀 Conclusiones y mejoras futuras
_👉 [Reflexión sobre el proyecto, qué ha funcionado, qué se puede mejorar, ideas para siguientes versiones]_
