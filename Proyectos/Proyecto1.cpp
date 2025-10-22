#include<iostream>
#include<cstring>
#include<iomanip>
#include<ctime>
#include <locale>

using namespace std;

void imprimirOpciones(){
	
	cout<<"SISTEMA DE GESTION HOSPITALARIA" <<endl;
	cout<<"1.Gestion de pacientes"<<endl;
	cout<<"2.Gestion de doctores"<<endl;
	cout<<"3.Gestion de citas"<<endl;
	cout<<"4. Salir"<< endl;
	cout<<"Ingrese la opcion que desee:"<<endl;
}

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

struct Cita {
    int id;
    int idPaciente;
    int idDoctor;
    char fecha[11];
    char hora[6];
    char motivo[150];
    char estado[20];
    char observaciones[200];
    bool atendida;
};

struct Paciente {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    int edad;
    char sexo;
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    
    HistorialMedico* historial;
    int cantidadConsultas;
    int capacidadHistorial;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    char alergias[500];
    char observaciones[500];
    bool activo;
};

struct Doctor {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    
    int* pacientesAsignados;
    int cantidadPacientes;
    int capacidadPacientes;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    
    bool disponible;
};

struct Hospital {
    char nombre[100];
    char direccion[150];
    char telefono[15];
    
    Paciente* pacientes;
    int cantidadPacientes;
    int capacidadPacientes;
    
    Doctor* doctores;
    int cantidadDoctores;
    int capacidadDoctores;
    
    Cita* citas;
    int cantidadCitas;
    int capacidadCitas;
    
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;
};

//Inicializar hospiatl
Hospital *inicializarHospital ( const char *nombre, const char *direccion, const char *telefono){
	Hospital *hospital = new Hospital;

	strncpy(hospital ->nombre, nombre, 100);
	strncpy(hospital -> direccion, direccion,150);
	strncpy(hospital ->telefono, telefono,15);

	hospital ->cantidadPacientes = 10;
	hospital ->cantidadPacientes = 0;
	hospital ->pacientes = new Paciente[hospital ->capacidadPacientes];

	hospital ->cantidadDoctores= 10;
	hospital ->cantidadDoctores= 0;
	hospital ->doctores= new Doctor [hospital ->capacidadDoctores];

	hospital->capacidadCitas = 20;
	hospital->capacidadCitas = 0;
	hospital ->citas = new Cita[hospital-> capacidadCitas];

	hospital ->siguienteIdPaciente=1;
	hospital -> siguienteIdDoctor=1;
	hospital ->siguienteIdCita=1;
	hospital ->siguienteIdConsulta=1;

	return hospital;
}

//PACIENTES
//Buscando el paciente por su cedula de identidad (v-)
Paciente* buscarPacientePorCedula(Hospital* hospital, const char* cedulaBuscada) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strcmp(hospital->pacientes[i].cedula, cedulaBuscada) == 0) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr; 
}
bool cedulaExiste(Hospital* hospital, const char* cedulaBuscada) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strcmp(hospital->pacientes[i].cedula, cedulaBuscada) == 0) {
            return true;
        }
    }
    return false;
}

//c)Buscando el paciente por ID
Paciente* buscarPacientePorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}

//1)crear paciente y se utiliza la funcion de redimensionar (se sustituye en el codigo)
Paciente* crearPaciente(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula,
                        int edad, char sexo,
                        const char* tipoSangre, const char* telefono, const char* direccion,
                        const char* email, const char* alergias, const char* observaciones){
						
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strcmp(hospital->pacientes[i].cedula, cedula) == 0) {
            cout << "Error: Esta cédula ya se encuentra registrada.\n";
            return nullptr;
        }
    }

    if (hospital->cantidadPacientes >= hospital->capacidadPacientes) {
        int nuevaCapacidad = hospital->capacidadPacientes * 2; //uplicar el arreglo, el examen
        Paciente* nuevoArray = new Paciente[nuevaCapacidad];
        for (int i = 0; i < hospital->cantidadPacientes; i++) {
            nuevoArray[i] = hospital->pacientes[i];
        }
        delete[] hospital->pacientes;
        hospital->pacientes = nuevoArray;
        hospital->capacidadPacientes = nuevaCapacidad;
    }

Paciente& nuevo= hospital->pacientes [hospital ->cantidadPacientes];

nuevo.id = hospital ->siguienteIdPaciente++;
strcpy (nuevo.nombre, nombre, 50);
strcpy (nuevo.apellido, apellido, 50);
strcpy (nuevo.cedula, cedula, 20);
nuevo.edad=edad;
nuevo.sexo= sexo;
strcpy (nuevo. tipoSangre, tipoSangre, 5);
strcpy (nuevo. telefono, telefono, 15);
strcpy (nuevo.direccion, direccion,100);
strcpy (nuevo. email, email,50);
strcpy(nuevo.alergias, alergias, 500);
strcpy (nuevo.observaciones, observaciones, 500);
nuevo.activo = true;

nuevo.capacidadHistorial=5;
nuevo.cantidadConsultas=0;
nuevo.historial = new HistorialMedico[nuevo.capacidadHistorial];

nuevo.capacidadCitas = 5;
nuevo.cantidadCitas = 0;
nuevo.citasAgendadas = new int[nuevo.capacidadCitas];

hospital -> cantidadPacientes++;
return &nuevo;
}

//d)Buscar paciente por nombre
void buscarPacientesPorNombre(Hospital* h, const char* fragmento) {
    cout << "\nPacientes que coinciden con \"" << fragmento << "\":\n";
    for (int i = 0; i < h->cantidadPacientes; i++) {
        if (strstr(h->pacientes[i].nombre, fragmento) != nullptr) {
            cout << "ID: " << h->pacientes[i].id << " | " << h->pacientes[i].nombre << " " << h->pacientes[i].apellido << "\n";
        }
    }
}

//mostrar historial medico
void mostrarHistorialMedico(Paciente* paciente) {
    if (paciente->cantidadHistorial == 0) {
        cout << "Este paciente no tiene historial médico registrado.\n";
        return;
    }

    cout << "\nHistorial Médico del Paciente:\n";
    for (int i = 0; i < paciente->cantidadHistorial; i++) {
        HistorialMedico& h = paciente->historial[i];
        cout << "\nConsulta #" << h.idConsulta << "\n";
        cout << "Fecha: " << h.fecha << "   Hora: " << h.hora << "\n";
        cout << "Diagnóstico: " << h.diagnostico << "\n";
        cout << "Tratamiento: " << h.tratamiento << "\n";
        cout << "Medicamentos: " << h.medicamentos << "\n";
        cout << "ID Doctor: " << h.idDoctor << "\n";
        cout << "Costo: $" << h.costoConsulta << "\n";
    }
}

// Actualizar datos del paciente
bool actualizarPaciente(Hospital* hospital, int id) {
    Paciente* p = buscarPacientePorId(hospital, id);
    if (!p) return false;

    cin.ignore();
    cout << "Nombre actual: " << p->nombre << "\nNuevo nombre: "; cin.getline(p->nombre, 50);
    cout << "Apellido actual: " << p->apellido << "\nNuevo apellido: "; cin.getline(p->apellido, 50);
    cout << "Edad actual: " << p->edad << "\nNueva edad: "; cin >> p->edad;
    cout << "Sexo actual: " << p->sexo << "\nNuevo sexo (M/F): "; cin >> p->sexo;
    cin.ignore();
    cout << "Tipo de sangre actual: " << p->tipoSangre << "\nNuevo tipo de sangre: "; cin.getline(p->tipoSangre, 5);
    cout << "Teléfono actual: " << p->telefono << "\nNuevo teléfono: "; cin.getline(p->telefono, 15);
    cout << "Dirección actual: " << p->direccion << "\nNueva dirección: "; cin.getline(p->direccion, 100);
    cout << "Email actual: " << p->email << "\nNuevo email: "; cin.getline(p->email, 50);
    cout << "Alergias actuales: " << p->alergias << "\nNuevas alergias: "; cin.getline(p->alergias, 500);
    cout << "Observaciones actuales: " << p->observaciones << "\nNuevas observaciones: "; cin.getline(p->observaciones, 500);
    return true;
}

//Lsta de pacientes
void listarPacientes(Hospital* hospital) {
    cout << "\nListado de Pacientes\n";
    cout << left << setw(5) << "ID"
         << setw(15) << "Nombre"
         << setw(15) << "Apellido"
         << setw(15) << "Cédula"
         << setw(6) << "Edad"
         << setw(10) << "Consultas" << "\n";

    cout << string(66, '-') << "\n"; // Línea divisoria

    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        Paciente& p = hospital->pacientes[i];
        cout << left << setw(5) << p.id
             << setw(15) << p.nombre
             << setw(15) << p.apellido
             << setw(15) << p.cedula
             << setw(6) << p.edad
             << setw(10) << p.cantidadConsultas << "\n";
    }
}

//eliminar pacientes
bool eliminarPaciente(Hospital* h, int id) {
    for (int i = 0; i < h->cantidadPacientes; i++) {
        if (h->pacientes[i].id == id) {
            delete[] h->pacientes[i].historial;

            // Eliminar citas
            for (int j = 0; j < h->cantidadCitas; j++) {
                if (h->citas[j].idPaciente == id) {
                    h->citas[j].idPaciente = -1;
                    strcpy(h->citas[j].estado, "Cancelada");
                }
            }

            // Remover de doctores
            for (int d = 0; d < h->cantidadDoctores; d++) {
                Doctor& doc = h->doctores[d];
                for (int p = 0; p < doc.cantidadPacientes; p++) {
                    if (doc.pacientesAsignados[p] == id) {
                        for (int k = p; k < doc.cantidadPacientes - 1; k++) {
                            doc.pacientesAsignados[k] = doc.pacientesAsignados[k + 1];
                        }
                        doc.cantidadPacientes--;
                        break;
                    }
                }
            }

            // Compactar arreglo
            for (int k = i; k < h->cantidadPacientes - 1; k++) {
                h->pacientes[k] = h->pacientes[k + 1];
            }
            h->cantidadPacientes--;
            return true;
        }
    }
    return false;
}

//Agregar historial medico
bool agregarHistorialMedico(Paciente* paciente, const char* fecha, const char* hora,
                            const char* diagnostico, const char* tratamiento,
                            const char* medicamentos, int idDoctor, float costo) {
 
    if (!paciente) return false;

    // Verificar si hay que duplicar el arreglo
    if (paciente->cantidadHistorial >= paciente->capacidadHistorial) {
        int nuevaCapacidad = paciente->capacidadHistorial * 2;
        HistorialMedico* nuevoHistorial = new HistorialMedico[nuevaCapacidad];

        // Copiar datos existentes
        for (int i = 0; i < paciente->cantidadHistorial; i++) {
            nuevoHistorial[i] = paciente->historial[i];
        }

        // Liberar memoria anterior
        delete[] paciente->historial;
        paciente->historial = nuevoHistorial;
        paciente->capacidadHistorial = nuevaCapacidad;
    }

    // Agregar nueva entrada
    HistorialMedico& h = paciente->historial[paciente->cantidadHistorial];
    h.idConsulta = paciente->cantidadHistorial + 1;

    strncpy(h.fecha, fecha, 10); h.fecha[10] = '\0';
    strncpy(h.hora, hora, 5); h.hora[5] = '\0';
    strncpy(h.diagnostico, diagnostico, 199); h.diagnostico[199] = '\0';
    strncpy(h.tratamiento, tratamiento, 199); h.tratamiento[199] = '\0';
    strncpy(h.medicamentos, medicamentos, 149); h.medicamentos[149] = '\0';

    h.idDoctor = idDoctor;
    h.costoConsulta = costo;

    paciente->cantidadHistorial++;
    paciente->cantidadConsultas++; // opcional

    return true;
}

//Haciendo el menu de pacientes
void imprimirMenudePacientes(Hospital*hospital){
int opcionpacientesw;
do{
cout << "\n===== MENÚ DE PACIENTES =====\n";
        cout << "1. Registrar nuevo paciente\n";
        cout << "2. Buscar paciente por cédula\n";
        cout << "3. Buscar paciente por nombre\n";
        cout << "4. Ver historial médico completo\n";
        cout << "5. Actualizar datos del paciente\n";
        cout << "6. Listar todos los pacientes\n";
        cout << "7. Eliminar paciente\n";
        cout << "8. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcionpacientesw;
        cin.ignore();

       switch (opcionpacientesw) {
            case 1: {
                char nombre[50], apellido[50], cedula[20];
                int edad;
                char sexo;

                cout << "Nombre: "; cin.getline(nombre, 50);
                cout << "Apellido: "; cin.getline(apellido, 50);
                cout << "Cédula: "; cin.getline(cedula, 20);
                cout << "Edad: "; cin >> edad; cin.ignore();
                cout << "Sexo (M/F): "; cin >> sexo; cin.ignore();

                Paciente* nuevo = crearPaciente(hospital, nombre, apellido, cedula, edad, sexo);
                if (nuevo) {
                    cout << "Paciente registrado con ID: " << nuevo->id << endl;
                }
				break;
            }
			case 2: {
				char cedula[20];
                cout << "Ingrese la cédula: ";
                cin.getline(cedula, 20);
                Paciente* p = buscarPacientePorCedula(hospital, cedula);
                if (p) {
                    cout << "Paciente encontrado: " << p->nombre << " " << p->apellido << " (ID " << p->id << ")\n";
                } else {
                    cout << "Paciente no encontrado.\n";
                }
                break;
			}
			 case 3: {
                char nombre[50];
                cout << "Ingrese el nombre a buscar: ";
                cin.getline(nombre, 50);

                int cantidad = 0;
                Paciente** encontrados = buscarPacientePorNombre(hospital, nombre, &cantidad);

                if (cantidad == 0) {
                    cout << "No se encontraron pacientes con ese nombre.\n";
                } else {
                    cout << "Pacientes encontrados:\n";
                    for (int i = 0; i < cantidad; i++) {
                        Paciente* p = encontrados[i];
                        cout << "ID: " << p->id << " - " << p->nombre << " " << p->apellido << " - Cédula: " << p->cedula << endl;
                    }
                    delete[] encontrados;
                }
                break;
            }
			 case 4: {
                int id;
                cout << "Ingrese el ID del paciente: ";
                cin >> id; cin.ignore();

                Paciente* p = buscarPacientePorId(hospital, id);
                if (p) {
                    mostrarHistorialMedico(p);
                } else {
                    cout << "Paciente no encontrado.\n";
                }
                break;
				}
            case 5: {
                int id;
                cout << "Ingrese el ID del paciente a actualizar: ";
                cin >> id; cin.ignore();
                Paciente* p = buscarPacientePorId(hospital, id);
                if (p) {
                    actualizarDatosPaciente(p);
                } else {
                    cout << "Paciente no encontrado.\n";
                }
                break;
            }
			case 6:
                listarPacientes(hospital);
                break;
            case 7: {
                int id;
                cout << "Ingrese el ID del paciente a eliminar: ";
                cin >> id; cin.ignore();
                eliminarPaciente(hospital, id);
                break;
            }
            case 8:
                cout << "Volviendo al menú principal\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcionpacientesw != 8);

}


//DOCTORES
Doctor* crearDoctor (Hospital*hospital, const char*nombre, const char* apellido, const char* cedula, const char* especialidad, int anosExperiencia,float costoConsulta ){
 if (hospital->cantidadDoctores >= hospital->capacidadDoctores){
	int nuevaCapacidad = hospital ->capacidadDoctores *2;
	Doctor* nuevoarreglo = new Doctor[nuevaCapacidad];
	for (int i = 0; i < hospital->cantidadDoctores; i++) {
            nuevoarreglo[i] = hospital->doctores[i];
        }
		delete [] hospital->doctores;
		hospital->doctores=nuevoarreglo;
		hospital->capacidadDoctores = nuevaCapacidad;
 }
	
}
int main(){
	Hospital*hospital= inicializarHospital("Hospital Universitario de Caracas", "Avenida Minerva y Avenida Interna UCV, Zona Médica, Los Chagauramos, Municipio Libertador.", " 02126067652");

	int opciongestion = 0;
	while(opciongestion != 4){
		
	imprimirOpciones();
	cin>> opciongestion;


switch (opciongestion){
	case 1:
	imprimirMenudePacientes (hospital);
			break;
	case 2:
	int opciondoctorsw=0;
	while (opciondoctorsw!=8){
		cout<<"1.Registrar nuevo doctor"<<endl;
		cout<<"2.Buscar doctor por ID"<<endl;
		cout<<"3.Buscar doctores por especialidad"<<endl;
		cout<<"4.Asignar paciente a doctor"<<endl;
		cout<<"5.Ver pacientes asignados a doctores"<<endl;
		cout<<"6.Listar todos los doctores"<<endl;
		cout<<"7.Eliminar doctor"<<endl;
		cout<<"8.Volver al menu principal"<<endl;
		cin>>opciondoctorsw;
		
		switch (opciondoctorsw){
			case 1:
				cout<<"Se ha registrado un nuevo doctor"<<endl;
			break;
			
			case 2:
				cout<<"El doctor por ID es:"<<endl;
			break;
			
		    case 3:
		    	cout<<"El doctor por la especialidad fue"<<endl;
		    break;
		    
		    case 4:
		    	cout<<"El paciente asignado al doctor fue:"<<endl;
		    break;
		    
		    case 5:
		    	cout<<"lista de pacinetes asignados a doctores es:"<<endl;
		    break;
		    
		    case 6:
		    	cout<<"lista para todos los doctores"<<endl;
		    break;
		    
		    case 7:
		    	cout<<"El doctor fue eliminado"<<endl;
		    break;
		    
		    case 8:
		    	cout<<"volver al menu principal"<<endl;
		    break;
		}
	}
		
		break;
	
	case 3:
	int opcioncitasw=0;
	while (opcioncitasw!=8){
		cout<<"1.Agendar nueva cita"<<endl;
		cout<<"2.Cancelar cita"<<endl;
		cout<<"3.Atender cita"<<endl;
		cout<<"4. Ver citas de un paciente"<<endl;
		cout<<"5. Ver citas de un doctor"<<endl;
		cout<<"6. Ver citas de una fecha"<<endl;
		cout<<"7. Ver citas pendientes"<<endl;
		cout<<"8. Volver al menu principal"<<endl;
		cin>>opcioncitasw;
		
		switch (opcioncitasw){
			case 1:
		    	cout<<"La cita fue agendada"<<endl;
		    break;
		    
		    case 2:
		    	cout<<"La cita fue cancelada"<<endl;
		    break;
		    
		    case 3:
		    	cout<<"La cita por atender es"<<endl;
		    break;
		    
		    case 4:
		    	cout<<"Las citas del paciente son"<<endl;
		    break;
		    
		    case 5:
		    	cout<<"Las citas del doctor son"<<endl;
		    break;
		    
		    case 6:
		    	cout<<"Las citas de la fecha son"<<endl;
		    break;
		    
		    case 7:
		    	cout<<"Las citas pendientes son"<<endl;
		    break;
		    
		    case 8:
		    	cout<<"Volver al menu principal"<<endl;
		    break;
		}
	}
		
		break;
		
	default: cout<<"Ingrese numeros del 1-4"<<endl;
}	
	
	return 0;
}
}
