# 🏥 Sistema de Gestión Hospitalaria en C++

Este proyecto se basa en crear un sistema hospitalario que permita administrar los pacientes, doctores, citas medicas e historiales medicos. A travez del sistema se busca 
mejorar la parte administrativa del hospital obteniendo una mejor organizacion de los datos peritinentes para garantizar que el servicio se lleve acabo de una manera efectiva, eficaz y
eficiente. Mejorando la experiencia del paciente y del personal medico de la institucion. 


## 📦 Estructura del sistema

El sistema se organiza en torno a una estructura principal llamada `Hospital`, que contiene arreglos dinámicos de:

- `Paciente`: con historial médico, citas agendadas, datos personales y estado activo.
- `Doctor`: con pacientes asignados, citas, especialidad y disponibilidad.
- `Cita`: con fecha, hora, motivo, estado y observaciones.
- `HistorialMedico`: con diagnóstico, tratamiento, medicamentos y costo.

## 🧠 Funcionalidades principales

### 👨‍⚕️ Gestión de Pacientes
- Registro de nuevos pacientes con validación de cédula y correo electrónico.
- Búsqueda por ID, cédula o fragmento de nombre.
- Actualización de datos personales.
- Eliminación lógica del paciente (cancelación de citas, desvinculación de doctores).
- Listado completo de pacientes.
- Agregado y visualización del historial médico.

### 🩺 Gestión de Doctores
- Registro de nuevos doctores con validación de cédula.
- Búsqueda por ID o especialidad.
- Asignación de pacientes.
- Visualización de pacientes asignados.
- Eliminación de doctores.

### 📅 Gestión de Citas
- Agendamiento de citas con validación de fecha y hora.
- Cancelación de citas no atendidas.
- Verificación de disponibilidad horaria.
- Visualización de citas por paciente, doctor, fecha o estado.
- Atención de citas con registro automático en el historial médico.

## 🔍 Validaciones incluidas
- Fecha en formato `YYYY-MM-DD` con verificación de días válidos y años bisiestos.
- Hora en formato `HH:MM` con rango válido.
- Email con presencia de `@` y `.` en orden correcto.

## 🧹 Limpieza de memoria
Al finalizar el programa, se libera toda la memoria dinámica utilizada para evitar fugas.

## 🖥️ Ejecución
El programa inicia con un menú principal que permite navegar entre las tres áreas de gestión. Cada sección tiene submenús interactivos para realizar las operaciones disponibles.

## 📌 Notas técnicas
- Se utiliza `strncpy` y `strcpy` para manejar cadenas estilo C.
- Los arreglos dinámicos se redimensionan automáticamente al alcanzar su capacidad.
- Se emplean referencias (`&`) para manipular directamente los datos en memoria.
- El sistema está diseñado para ser extendible y modular.
