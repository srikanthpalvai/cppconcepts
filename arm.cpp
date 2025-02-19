#include <memory>
#include <iostream>
#include <vector>
#include <cstdint>

struct Image {
    int width;
    int height;
    std::unique_ptr<uint8_t[]> data;
    // assume the metadata is unique to each image
    std::shared_ptr<int> metadata;

    Image(int w, int h) : width(w), height(h),
        data(std::make_unique<uint8_t[]>(w * h)),
        metadata(std::make_shared<int>(0)) {
            std::cout << "Parameter ctor " << std::endl;
        }

    Image(Image&& other) noexcept :
        width(other.width), height(other.height),
        data(std::move(other.data)),
        metadata(std::move(other.metadata)) {}

    Image(const Image& other) : width(other.width), height(other.height),
        data(std::make_unique<uint8_t[]>(width * height)),
        metadata(std::make_shared<int>(*other.metadata)) {} // Deep copy of metadata

    void invert() {
        auto temp = std::make_unique<uint8_t[]>(width * height);
        for (int i = 0; i < width * height; i++) { // Fixed off-by-one error
            temp[i] = (255 - data[i]);
        }
        data = std::move(temp);
    }

    int size() const {
        return width * height; // Changed to width * height, not width + height
    }
};

std::shared_ptr<Image> create_image(int w, int h) {
    return std::make_shared<Image>(w, h);
}

uint8_t process_buffers(const std::vector<uint8_t>& buf) { // Passed by constant reference to avoid modifying original
    uint8_t sum = 0;
    for (auto pixel : buf) {
        std::cout << "pixel"  << pixel << std::endl;
        uint8_t modified_pixel = pixel - 128;
        std::cout << "modidied_pixel"  << modified_pixel << std::endl;
        sum += modified_pixel;
    }
    std::cout << "Inside sum:" << static_cast<int>(sum) << std::endl;
    return sum;
}
void print_buffers(const std::vector<uint8_t>& buffer) {

    for(auto buf : buffer){
        std::cout << buf << std::endl; 
    }
}

// Function to print part of the image
void print_image(const Image& img, int start, int size) {
    // Print pixel data from 'start' to 'size' (or the range of the array)
    for (int i = start; i < size && i < img.size(); ++i) {
        std::cout << static_cast<int>(img.data[i]) << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto img = create_image(640, 480);
     int size = img->size();
     std::vector<uint8_t> buffer(img->data.get(), img->data.get() + size);
     auto sum = process_buffers(buffer);
     std::cout << "sum: "<< sum << std::endl;
     print_buffers(buffer);
     std::copy(buffer.begin(), buffer.end(), img->data.get());
    
    auto unique_img = std::make_unique<Image>(*img);
    print_image(*unique_img, 0, 10); // Print first 10 pixels of the image

    unique_img->invert();

    std::vector<Image> images;
    images.emplace_back(10, 10);

    for (auto& img_ref : images) { // Changed to reference to avoid unnecessary copying
        img_ref.invert();
    }

    // Correctly moving img into moved object
    Image moved = std::move(images[0]);
    //img is now in a moved-from state, so we shouldn't use it after this.
    img->invert(); // This should not be accessed after moving.
}
