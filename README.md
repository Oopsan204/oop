# Chinese Chess (Cờ Tướng)

Chinese Chess (Cờ Tướng) là một phần mềm mô phỏng trò chơi cờ tướng, được phát triển bằng ngôn ngữ lập trình C++ và sử dụng thư viện Qt để xây dựng giao diện người dùng. Phần mềm này cho phép người chơi trải nghiệm trò chơi cờ tướng trên máy tính với các tính năng cơ bản như di chuyển quân cờ, kiểm tra nước đi hợp lệ và hiển thị bàn cờ.

## Tính năng chính

- Hiển thị bàn cờ và các quân cờ với hình ảnh trực quan.
- Cho phép người chơi di chuyển các quân cờ theo luật cờ tướng.
- Kiểm tra tính hợp lệ của các nước đi.
- Lưu và tải lại trạng thái của trò chơi.

## Cấu trúc dự án

Dự án bao gồm các tệp và thư mục chính sau:

- `Board.cpp` và `Board.h`: Quản lý bàn cờ và các quân cờ trên bàn cờ.
- `Chess.cpp` và `Chess.h`: Định nghĩa các quân cờ và các phương thức liên quan.
- `GameManager.cpp` và `GameManager.h`: Quản lý trò chơi, bao gồm việc khởi tạo và điều khiển trò chơi.
- `viewer.cpp` và `viewer.h`: Xây dựng giao diện người dùng bằng Qt.
- `main.cpp`: Tệp chính để khởi động ứng dụng.
- `img/`: Thư mục chứa các hình ảnh của quân cờ và bàn cờ.
- `test/`: Thư mục chứa các tệp kiểm thử và Makefile để xây dựng dự án.

## Hướng dẫn cài đặt và sử dụng

### Yêu cầu hệ thống

- Hệ điều hành: Windows, macOS hoặc Linux
- Trình biên dịch: g++ hoặc clang++
- Thư viện: Qt 6.8.1 hoặc phiên bản mới hơn

### Cài đặt

1. Clone repository từ GitHub:
    ```sh
    git clone <repository-url>
    cd ChineseChess
    ```

2. Cài đặt các thư viện cần thiết:
    ```sh
    sudo apt-get install qt6-base-dev
    ```

3. Xây dựng dự án:
    ```sh
    qmake ChineseChess.pro
    make
    ```

4. Chạy ứng dụng:
    ```sh
    ./ChineseChess
    ```

## Đóng góp

Chúng tôi hoan nghênh mọi đóng góp từ cộng đồng. Nếu bạn muốn đóng góp, vui lòng fork repository, tạo branch mới và gửi pull request.

