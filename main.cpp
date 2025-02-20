#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>

std::string getTimestampFilename() {
    std::time_t now = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "snapshot_%Y%m%d_%H%M%S.jpg", std::localtime(&now));
    return std::string(buffer);
}

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open webcam.\n";
        return -1;
    }

    cv::Mat frame;
    std::cout << "Press 's' to capture a snapshot, 'q' to quit.\n";

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cv::imshow("Webcam", frame);
        char key = cv::waitKey(30);

        if (key == 's') {
            std::string filename = getTimestampFilename();
            cv::imwrite(filename, frame);
            std::cout << "Snapshot saved as " << filename << "\n";
        }
        else if (key == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
