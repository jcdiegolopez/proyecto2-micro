//Proyecto 2 Microprocesadores
//Programa de reescalado de imagen
//Forma: PARALELA

#include <opencv2/opencv.hpp>
#include <math.h>
#include <omp.h>

// Funcion para redimensionar una fraccion de la imagen de manera secuencial
void image_resize_task(const cv::Mat& original, cv::Mat& new_image, double scale, int i_start, int i_end) {
    for (int i = i_start; i < i_end; i++) {
        for (int j = 0; j < new_image.cols; j++) {

            // Calcular las coordenadas originales correspondientes en la imagen original
            double original_y = i / scale;
            double original_x = j / scale;

            // Encontrar los pIxeles vecinos mas cercanos
            int x1 = (int)floor(original_x);
            int x2 = std::min((int)ceil(original_x), original.cols - 1);
            int y1 = (int)floor(original_y);
            int y2 = std::min((int)ceil(original_y), original.rows - 1);

            // Calcular la interpolacion bilineal para el valor del pixel
            double dx = original_x - x1;
            double dy = original_y - y1;

            double x_bottom = original.at<uchar>(y1, x1) * (1 - dx) + original.at<uchar>(y1, x2) * dx;
            double x_top = original.at<uchar>(y2, x1) * (1 - dx) + original.at<uchar>(y2, x2) * dx;
            double value = x_bottom * (1 - dy) + x_top * dy;

            new_image.at<uchar>(i, j) = (uchar)value;
        }
    }
}

// Función para redimensionar la imagen completa
void image_resize(const cv::Mat& original, cv::Mat& new_image, double scale) {
    
    // Calcular las nuevas dimensiones de la imagen
    int new_height = (int)(original.rows * scale);
    int new_width = (int)(original.cols * scale);

    new_image = cv::Mat::zeros(new_height, new_width, original.type());

 // Ejecutar el redimensionamiento en paralelo
#pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int chunk_size = new_height / num_threads;

 // Dividir la imagen en partes para que cada hilo procese una fracción
#pragma omp for
        for (int i = 0; i < num_threads; i++) {
            int i_start = i * chunk_size;
            int i_end = (i == num_threads - 1) ? new_height : i_start + chunk_size;
            image_resize_task(original, new_image, scale, i_start, i_end);
        }
    }
}

int main() {
    
    // Cargar la imagen original en escala de grises
    const char* image_path = "./images/sample.jpg";
    const char* output_path = "./images/rescaled_image.jpg";

    cv::Mat original_image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    if (original_image.empty()) {
        printf("Error: No se pudo abrir o encontrar la imagen.\n");
        return -1;
    }

    printf("Imagen Original: %d x %d\n", original_image.rows, original_image.cols);

    // Definir el factor de escala y redimensionar la imagen
    double scale = 2;
    cv::Mat new_image;
    double start_time = omp_get_wtime(); 
    image_resize(original_image, new_image, scale);
    double end_time = omp_get_wtime(); 
    double elapsed_time = (end_time - start_time) * 1000.0; 

    printf("Imagen redimensionada: %d x %d\n", new_image.rows, new_image.cols);
    printf("Tiempo de ejecucion: %.2f ms\n", elapsed_time);


    // Guardar la nueva imagen redimensionada
    cv::imwrite(output_path, new_image);

    return 0;
}

