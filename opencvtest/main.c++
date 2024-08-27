//Proyecto 2 Microprocesadores
//Programa de reescalado de imagen
//Forma: SECUENCIAL

#include <opencv2/opencv.hpp>
#include <math.h>
#include <omp.h>

// FunciOn para redimensionar la imagen
void image_resize(const cv::Mat& original, cv::Mat& new_image, double scale) {
    
    // Calcular las nuevas dimensiones de la imagen escalada
    int new_height = (int)(original.rows * scale);
    int new_width = (int)(original.cols * scale);

    // Crear una nueva imagen con las nuevas dimensiones 
    new_image = cv::Mat::zeros(new_height, new_width, original.type());

    // Bucle para recorrer la nueva imagen y calcular los valores de los pIxeles
    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            double original_y = i / scale;
            double original_x = j / scale;

            // Obtener los índices de los pixeles vecinos en la imagen original
            int x1 = (int)floor(original_x);
            int x2 = std::min((int)ceil(original_x), original.cols - 1);
            int y1 = (int)floor(original_y);
            int y2 = std::min((int)ceil(original_y), original.rows - 1);

            // Calcular las distancias relativas en x y y
            double dx = original_x - x1;
            double dy = original_y - y1;

            // Interpolacion bilineal para calcular el valor del pixel
            double x_bottom = original.at<uchar>(y1, x1) * (1 - dx) + original.at<uchar>(y1, x2) * dx;
            double x_top = original.at<uchar>(y2, x1) * (1 - dx) + original.at<uchar>(y2, x2) * dx;
            double value = x_bottom * (1 - dy) + x_top * dy;

            new_image.at<uchar>(i, j) = (uchar)value;
        }
    }
}

int main() {
    const char* image_path = "./images/sample.jpg";
    const char* output_path = "./images/rescaled_image.jpg";

    // Leer la imagen en escala de grises
    cv::Mat original_image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    if (original_image.empty()) {
        printf("Error: No se pudo abrir o encontrar la imagen.\n");
        return -1;
    }

    printf("Imagen Original: %d x %d\n", original_image.rows, original_image.cols);

    // Escala de redimensionamiento
    double scale = 0.5;
    cv::Mat new_image;

    // Redimensionar la imagen 
    image_resize(original_image, new_image, scale);

    printf("Imagen redimensionada: %d x %d\n", new_image.rows, new_image.cols);

    // Guardar la nueva imagen en el archivo de salida
    cv::imwrite(output_path, new_image);

    return 0;
}
