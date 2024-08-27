# Proyecto 02 Microprocesadores: Image Rescaling with OpenMP

## Integrantes
- Diego José López Campos 23242
- Genser Catalán 23401
- Luis Palacios 23933

## Descripción del Proyecto
Este proyecto implementa un programa que reescala imágenes utilizando interpolación bilineal. La implementación hace uso de OpenCV para el manejo de imágenes y OpenMP para paralelizar el proceso, mejorando así el rendimiento en sistemas con múltiples núcleos.

## Características
- Reescalado de imágenes usando interpolación bilineal
- Paralelización con OpenMP para mejorar el rendimiento
- Uso de OpenCV para leer y escribir imágenes

## Requisitos
- Visual Studio 2022
- OpenCV
- OpenMP (incluido en Visual Studio)

## Guía de Instalación

### 1. Instalación de Visual Studio 2022
Descargue e instale Visual Studio 2022 desde el sitio oficial de Microsoft e instale desktop tools for c++ developmet.

### 2. Instalación de OpenCV
Para instalar OpenCV en Visual Studio 2022, siga el tutorial en este video:
[Instalación de OpenCV en Visual Studio](https://www.youtube.com/watch?v=unSce_GPwto)

### 3. Configuración de OpenMP
Para habilitar OpenMP en su proyecto:
1. Abra su proyecto en Visual Studio 2022
2. Vaya a Project > Project Properties
3. Navegue a Configuration Properties > C/C++ > Language
4. Establezca "OpenMP Support" en "Yes"

## Uso
1. Clone este repositorio
2. Abra el proyecto en Visual Studio 2022
3. Compile y ejecute el programa
4. El programa leerá una imagen de entrada, la reescalará y guardará la imagen resultante

