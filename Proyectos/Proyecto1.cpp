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
Paciente* buscarPacientePorCedula (Hospital*hospital, const char*cedula){
	for (int i=0; i< hospital->cantidadPacientes; i++){
		if (strcasecmp(hospital->pacientes[i].cedula, cedula)==0){
			return &hospital->pacientes[i];
		}
	}
	return nullptr;
}

//c)Buscando el paciente por ID
Paciente* buscarPacientePorId(Hospital*hospital, int id){
	for (int i=0; i<hospital->cantidadPacientes; i++){
		if (hospital->pacientes[i].id == id){
			return &hospital->pacientes[i];
		}
	}
	return nullptr;
}

//Duplicar el arreglo(redimensionar/examen)
void redimensionararregloPacientes (Hospital *hospital){
	int nuevaCapacidad = hospital->capacidadPacientes * 2;
	Paciente * nuevoarreglo= new Paciente[nuevaCapacidad];

	for (int i=0; i<hospital ->cantidadPacientes; i++){
		nuevoarreglo [i]= hospital ->pacientes [i];
	}

	delete [] hospital ->pacientes;
	hospital ->pacientes= nuevoarreglo;
	hospital -> capacidadPacientes= nuevaCapacidad;
}

//1)crear paciente y se utiliza la funcion de redimensionar (se sustituye en el codigo)
Paciente *crearPaciente(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula, int edad, char sexo){
	for (int i=0; i<hospital->cantidadPacientes; i++)
if (strcasecmp (hospital->pacientes[i].cedula,cedula) ==0){
	cout<< "Error: La cedula ya se encuentra registrada."<< endl;
	return nullptr;
}
if (hospital ->cantidadPacientes >= hospital ->capacidadPacientes){
	redimensionararregloPacientes (hospital);
}

Paciente& nuevo= hospital->pacientes [hospital ->cantidadPacientes];

nuevo.id = hospital ->siguienteIdPaciente++;
strcpy (nuevo.nombre, nombre, 50);
strcpy (nuevo.apellido, apellido, 50);
strcpy (nuevo.cedula, cedula, 20);
nuevo.edad=edad;
nuevo.sexo= sexo;
strcpy (nuevo. tipoSangre, "");
strcpy (nuevo. telefono, "");
strcpy (nuevo.direccion, "");
strcpy (nuevo. email, "");
strcpy(nuevo.alergias, "");
strcpy (nuevo.observaciones, "");
nuevo.activo = true;

nuevo.capacidadHistorial=5;
nuevo.cantidadConsultas=0;
nuevo.historial = HistorialMedico[nuevo.capacidadHistorial];

nuevo.capacidadCitas = 5;
nuevo.cantidadCitas = 0;
nuevo.citasAgendadas = new int[nuevo.capacidadCitas];

hospital -> cantidadPacientes++;
return &nuevo;
}

//d)Buscar paciente por nombre
Paciente ** buscarPacientePorNombre(Hospital*hospital, const char*nombre, int* cantidad){
	int contador =0;
	for( int i=0; i< hospital->cantidadPacientes; i++){
		if (strstr(hospital->pacientes[i].nombre,nombre)){
			contador++;
		}
	}
	
	if(contador == 0){
		*cantidad=0;
		return nullptr;
	}

	Paciente** resultados= new Paciente*[contador];
	int index =0;
	for (int i=0; i< hospital->cantidadPacientes; i++){
		if (strstr(hospital->pacientes[i].nombre, nombre)){
			resultados[index++]= &hospital->pacientes[i];
		}
	}

	*cantidad = contador;
	return resultados;
}

void mostrarHistorialMedico(Paciente* paciente){
	if (paciente->cantidadConsultas==0){
		cout<<"Este paciente no tiene consultas registradas./n"<<endl;
		return;
	}

	cout<<"/nHistorial Medico de"<<paciente->nombre<<","<<paciente->apellido<<endl;
	cout<< left << setw (12)<< "Fecha"
	<< setw(8)<< "hora"
	<< setw(20)<< "Doctor ID"
	<< setw (30)<< "Diagnostico"
	<< setw (10)<< "Costo"<< endl;
	cout<< string (90, '-')<< endl;

	for (int i=0; i <paciente->cantidadConsultas;i++){
		HistorialMedico& h= paciente->historial[i];
		cout<< left << setw (12)<< h.fecha
		<<setw (8)<< h.hora
		<<setw (20)<< h.idDoctor
		<<setw (30)<< h.diagnostico
		<<setw (10)<< h.costo<<endl;
	}
}

// Actualizar datos del paciente
void actualizarDatosPaciente (Paciente* paciente){
	int opcion;
    do {
        cout << "\n--- Actualizar datos de " << paciente->nombre << " " << paciente->apellido << " ---\n";
        cout << "1. Nombre\n";
        cout << "2. Apellido\n";
        cout << "3. Edad\n";
        cout << "4. Sexo\n";
        cout << "5. Teléfono\n";
        cout << "6. Dirección\n";
        cout << "7. Email\n";
        cout << "8. Alergias\n";
        cout << "9. Observaciones\n";
        cout << "10. Salir\n";
        cout << "Seleccione el campo a actualizar: ";
        cin >> opcion;
        cin.ignore();

		switch (opcion) {
            case 1: {
                char nuevo[50];
                cout << "Nuevo nombre: "; cin.getline(nuevo, 50);
                strncpy(paciente->nombre, nuevo, 50);
                break;
            }
            case 2: {
                char nuevo[50];
                cout << "Nuevo apellido: "; cin.getline(nuevo, 50);
                strncpy(paciente->apellido, nuevo, 50);
                break;
            }
            case 3: {
                int edad;
				 cout << "Nueva edad: "; cin >> edad; cin.ignore();
                paciente->edad = edad;
                break;
            }
            case 4: {
                char sexo;
                cout << "Nuevo sexo (M/F): "; cin >> sexo; cin.ignore();
                paciente->sexo = sexo;
                break;
            }
			case 5: {
                char nuevo[15];
                cout << "Nuevo teléfono: "; cin.getline(nuevo, 15);
                strncpy(paciente->telefono, nuevo, 15);
                break;
            }
            case 6: {
                char nuevo[100];
                cout << "Nueva dirección: "; cin.getline(nuevo, 100);
                strncpy(paciente->direccion, nuevo, 100);
                break;
            }
            case 7: {
                char nuevo[50];
                cout << "Nuevo email: "; cin.getline(nuevo, 50);
                strncpy(paciente->email, nuevo, 50);
                break;
			}
            case 8: {
                char nuevo[500];
                cout << "Alergias: "; cin.getline(nuevo, 500);
                strncpy(paciente->alergias, nuevo, 500);
                break;
            }
            case 9: {
                char nuevo[500];
                cout << "Observaciones: "; cin.getline(nuevo, 500);
                strncpy(paciente->observaciones, nuevo, 500);
                break;
            }
            case 10:
                cout << "Saliendo de actualización...\n";
                break;
            default:
                cout << "Opción inválida.\n";
		}
    } while (opcion != 10);
}
//Lsta de pacientes
void listarPacientes(Hospital* hospital) {
    if (hospital->cantidadPacientes == 0) {
        cout << "No hay pacientes registrados.\n";
        return;
    }

	cout<<"\n Lista De Pacientes";
	for (int i=0; i<hospital->cantidadPacientes; i++){
         Paciente& p= hospital->pacientes[i];
		 cout<<"ID:"<<p.id<<"-"<<p.nombre << ","<<p.apellido
		 <<"-Cedula:"<<p.cedula<<"-Edad:"<<p.edad
		<< " - Sexo: " << p.sexo << endl;
	}
}

//eliminar pacientes
bool eliminarPaciente(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id) {
            for (int j = i; j < hospital->cantidadPacientes - 1; j++) {
                hospital->pacientes[j] = hospital->pacientes[j + 1];
            }
            hospital->cantidadPacientes--;
            cout << "Paciente eliminado exitosamente.\n";
            return true;
        }
    }
    cout << "Paciente no encontrado.\n";
    return false;
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
	// se itera para verificar que la cedula del doctor no este repetida
	for (int i=0; i<hospital ->cantidadDoctores; i++){
		if(strcasecmp(hospital ->doctores[i].cedula,cedula)== 0)
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
