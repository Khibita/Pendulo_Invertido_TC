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

## 🔍 Investigación y planteamiento
_👉 [Explicar investigaciones previas, referencias, problemas encontrados y planteamiento del proyecto]_

---

## 🛠️ Hardware
**Componentes usados:**
- ESP32: [modelo]
- Sensor: [ej. MPU6050]
- Driver de motor: [ej. TB6612FNG]
- Motores: [modelo]
- Batería: [tipo y características]
- Otros: [reguladores, cables, etc.]

_👉 [Incluir enlaces o esquemas de conexión si los hay]_

---

## 🧱 Diseño mecánico
**Software de diseño usado:**  
_👉 [Ej. Fusion 360, FreeCAD...]_

**Método de fabricación:**  
_👉 [Impresión 3D, corte láser...]_

**Versiones del chasis y decisiones de diseño:**  
_👉 [Breve resumen + imágenes si aplica]_

---

## 🔌 Montaje
_👉 [Explicación breve del ensamblado, conexiones y organización del sistema]_

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

_👉 [Describir brevemente cada prueba y resultados observados]_  
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
