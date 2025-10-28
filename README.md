Nombre del proyecto: Gestion hospitalaria
Este proyecto se basa en crear un sistema hospitalario que permita administrar los pacientes, doctores, citas medicas e historiales medicos. A travez del sistema se busca 
mejorar la parte administrativa del hospital obteniendo una mejor organizacion de los datos peritinentes para garantizar que el servicio se lleve acabo de una manera efectiva, eficaz y
eficiente. Mejorando la experiencia del paciente y dep personal medico de la institucion. 

Explicacion de las estructuras
struct HistorialMedico {
    int idConsulta;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;
}; 
En esta estructura se colocaron los datos necesarios para tener un historial medico, int idConsulta para saber que numero de consulta es, Char fecha y hora para saber a que hora se llevo
acabo la consulta, Char diagnostico,tratamiento, medicamentos es informacion medica proporcionada por el doctor que atendio la consulta, int idDoctor es para saber el id del doctor que 
fue asignado y por ultimo float costo que me permite saber el precio de la consulta.
