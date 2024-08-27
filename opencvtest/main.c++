#include <opencv2/opencv.hpp>
#include <math.h>
#include <omp.h>

void image_resize(const cv::Mat& original, cv::Mat& new_image, double scale) {
    int new_height = (int)(original.rows * scale);
    int new_width = (int)(original.cols * scale);

    new_image = cv::Mat::zeros(new_height, new_width, original.type());

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            double original_y = i / scale;
            double original_x = j / scale;

            int x1 = (int)floor(original_x);
            int x2 = std::min((int)ceil(original_x), original.cols - 1);
            int y1 = (int)floor(original_y);
            int y2 = std::min((int)ceil(original_y), original.rows - 1);

            double dx = original_x - x1;
            double dy = original_y - y1;

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

    cv::Mat original_image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    if (original_image.empty()) {
        printf("Error: No se pudo abrir o encontrar la imagen.\n");
        return -1;
    }

    printf("Imagen Original: %d x %d\n", original_image.rows, original_image.cols);

    double scale = 0.5;
    cv::Mat new_image;

    image_resize(original_image, new_image, scale);

    printf("Imagen redimensionada: %d x %d\n", new_image.rows, new_image.cols);

    cv::imwrite(output_path, new_image);

    return 0;
}
