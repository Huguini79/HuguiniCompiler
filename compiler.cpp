#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<windows.h>

#include "compiler.h"

using namespace std;

ofstream archivo;

void analizar_comando(const char* comando) {
  archivo.open("boothuguinicompiler.asm");
  archivo << "; Codigo generado por HuguiniCompiler" << endl << endl;
	archivo << "ORG 0x7c00" << endl;
  archivo << "BITS 16" << endl << endl;
  archivo << "start:" << endl;
  archivo << "      mov ah, 0x0E" << endl;
  int i = 0;
      while (comando[i] != '\0') {
        if(comando[i] == 'p' && 
        comando[i+1] == 'r' && 
        comando[i+2] == 'i' && 
        comando[i+3] == 'n' && 
        comando[i+4] == 't' &&
        comando[i+5] == 'h' &&
        comando[i+6] == 'c' &&
        comando[i+7] == 't' &&
        comando[i+8] == 'x' &&
        comando[i+9] == 't') {
          i += 10;
          
          while(comando[i] == ' ') i++;
          
          printf("\n");
          
          while(comando[i] != '\0') {
              char letra[2];
              letra[0] = comando[i];
              letra[1] = '\0';
              archivo << "      mov al, '" << letra << "'" << endl;
              archivo << "      int 0x10" << endl;
              i++;
          }

          archivo << endl;

          archivo << "times 510 - ($ - $$) db 0" << endl;
          archivo << "dw 0xAA55";
           
          return;

          
        }
        i++;
      }
      printf("Comando no reconocido");
}

int main() {
  ifstream archivo_entrada;
  ofstream archivo_build;
  archivo_entrada.open("programa.hc");
  archivo_build.open("build.bat");
  string linea;

while (getline(archivo_entrada, linea)) {
    analizar_comando(linea.c_str());
}
archivo_entrada.close();
  archivo_build << "nasm -f bin boothuguinicompiler.asm -o boot.bin" << endl;
  archivo_build << "qemu-system-x86_64 boot.bin";
  MessageBox(NULL, "PROGRAMA TRADUCIDO A ENSAMBLADOR REALIZADO EXITOSAMENTE, EJECUTA EL 'build.bat' QUE TE HE DEJADO EN LA CARPETA PARA QUE SE COMPILE Y SE EMULE CORRECTAMENTE", "PROGRAMA TRADUCIDO A ENSAMBLADOR REALIZADO EXITOSAMENTE", MB_OK);
}