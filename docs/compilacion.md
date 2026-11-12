# Guía de Compilación

### 1. Usando Visual Studio (Recomendado)
1. Abrir Visual Studio 2022.
2. Hacer doble clic en el archivo de solución (`.sln`) dentro de la carpeta del proyecto.
3. Presionar la tecla `F5` o el botón verde de "Depurador local de Windows" para compilar y ejecutar.

### 2. Usando la consola y el comando cl (Línea de comandos de MSVC)
1. Abrir la terminal "Developer Command Prompt for VS".
2. Navegar hasta la carpeta `/src`.
3. Ejecutar: `cl /EHsc *.cpp /Fe:Blackjack.exe`
4. Ejecutar el programa escribiendo: `Blackjack.exe`