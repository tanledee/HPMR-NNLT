#include <stdio.h>
#include <string.h> // Cần dùng cho strcpy, strcmp, và strcspn
#include <stdlib.h> // Không bắt buộc, nhưng hữu ích

// --- 0. Định nghĩa Cấu trúc Chung ---
// (Tất cả thành viên PHẢI dùng chung struct này)

struct SinhVien {
    char mssv[5];       // MSSV 4 chữ số
    char hoTen[50];
    char nhom;          // 'A' hoặc 'B'
    float diemQT;       // Điểm quá trình
    float diemKT;       // Điểm kiểm tra
    float diemThi;
    float diemTB;       // Điểm trung bình (sẽ được tính toán)
    char xepLoai[15];   // Xếp loại (sẽ được gán)
};

// Đặt tên viết tắt cho struct
typedef struct SinhVien SV;


// --- 0. Khai báo Nguyên mẫu Hàm (Prototypes) ---
// (Giúp hàm main có thể gọi các hàm bên dưới)

// Module 1 (Nhập/Xuất)
SV nhapMotSV();
void nhapDanhSach(SV ds[], int n);
void xuatMotSV(SV sv);
void xuatBangDiem(SV ds[], int n);

// Module 2 (Xử lý & Thống kê cơ bản)
float tinhDiemTB(SV sv);
const char* xepLoai(float diemTB);
void xuLyDanhSach(SV ds[], int n);
float tinhDiemTBLop(SV ds[], int n);
float tinhDiemTBNhom(SV ds[], int n, char tenNhom);
void thongKeXepLoai(SV ds[], int n);

// Module 3 (Thống kê Nâng cao)
float timDiemCaoNhatLop(SV ds[], int n);
float timDiemThapNhatLop(SV ds[], int n);
float timDiemCaoNhatNhom(SV ds[], int n, char tenNhom);
float timDiemThapNhatNhom(SV ds[], int n, char tenNhom);
void hoanVi(SV* a, SV* b);
void sapXepGiamDan(SV ds_copy[], int n);
void xuatTop3(SV ds[], int n);
void sapXepTangDan(SV ds_copy[], int n);
void xuatBottom3(SV ds[], int n);

// Module 4 (Hàm Main)
int main();


// --- 4. Module 4: Hàm Main (Trưởng nhóm) ---
// (Hàm điều phối chính)
// --- 4. Module 4: Hàm Main (Trưởng nhóm) ---
// (Hàm điều phối chính)
int main() {
    // 4.1. Khai báo biến
    const int soLuongSV = 2; // Đề bài yêu cầu 20 sinh viên
    SV danhSachLop[soLuongSV];
    float dtbLop, dtbNhomA, dtbNhomB;
    float maxLop, maxNhomA, maxNhomB;
    float minLop, minNhomA, minNhomB; // Thêm điểm thấp nhất

    // 4.2. Nhập dữ liệu
    printf("--- CHUONG TRINH QUAN LY DIEM SINH VIEN ---\n");
    printf("--- MOI BAN NHAP DU LIEU CHO %d SINH VIEN ---\n", soLuongSV);
    nhapDanhSach(danhSachLop, soLuongSV);
    printf("(!) Da nhap xong du lieu.\n");

    // 4.3. Xử lý dữ liệu (Tính toán)
    xuLyDanhSach(danhSachLop, soLuongSV);
    printf("(!) Da tinh toan xong diem TB va xep loai.\n");

    // 4.4. Xuất Bảng điểm tổng hợp
    printf("\n\n--- BANG DIEM TONG HOP CUA LOP ---\n");
    xuatBangDiem(danhSachLop, soLuongSV);

    // 4.5. Xuất các giá trị thống kê
    printf("\n\n--- CAC GIA TRI THONG KE CUA LOP ---\n");

    // Tính toán
    dtbLop = tinhDiemTBLop(danhSachLop, soLuongSV);
    dtbNhomA = tinhDiemTBNhom(danhSachLop, soLuongSV, 'A');
    dtbNhomB = tinhDiemTBNhom(danhSachLop, soLuongSV, 'B');

    maxLop = timDiemCaoNhatLop(danhSachLop, soLuongSV);
    maxNhomA = timDiemCaoNhatNhom(danhSachLop, soLuongSV, 'A');
    maxNhomB = timDiemCaoNhatNhom(danhSachLop, soLuongSV, 'B');

    minLop = timDiemThapNhatLop(danhSachLop, soLuongSV);
    minNhomA = timDiemThapNhatNhom(danhSachLop, soLuongSV, 'A');
    minNhomB = timDiemThapNhatNhom(danhSachLop, soLuongSV, 'B');


    // In ra
    printf("1. Diem trung binh:\n"); //
    printf("   + Lop: %.2f\n", dtbLop);
    printf("   + Nhom A: %.2f\n", dtbNhomA);
    printf("   + Nhom B: %.2f\n", dtbNhomB);

    // So sánh điểm 2 nhóm
    if (dtbNhomA > dtbNhomB) {
        printf("   => Diem TB nhom A cao hon nhom B.\n");
    } else if (dtbNhomB > dtbNhomA) {
        printf("   => Diem TB nhom B cao hon nhom A.\n");
    } else {
        printf("   => Diem TB hai nhom bang nhau.\n");
    }

    printf("\n2. Diem cao nhat:\n"); //
    printf("   + Lop: %.2f\n", maxLop);
    printf("   + Nhom A: %.2f\n", maxNhomA);
    printf("   + Nhom B: %.2f\n", maxNhomB);

    printf("\n3. Diem thap nhat:\n"); //
    printf("   + Lop: %.2f\n", minLop);
    printf("   + Nhom A: %.2f\n", minNhomA);
    printf("   + Nhom B: %.2f\n", minNhomB);

    printf("\n4. Top 3 sinh vien diem cao nhat lop:\n"); //
    xuatTop3(danhSachLop, soLuongSV);

    printf("\n5. Top 3 sinh vien diem thap nhat lop:\n"); //
    xuatBottom3(danhSachLop, soLuongSV);

    printf("\n6. Thong ke xep loai cua lop:\n"); //
    thongKeXepLoai(danhSachLop, soLuongSV);

    printf("\n--- KET THUC CHUONG TRINH ---\n");
    return 0; // Kết thúc chương trình
}


// --- 1. Module Nhập/Xuất (Người 1) ---

/**
 * @brief Hàm dọn dẹp bộ đệm input (stdin).
 * @note Cần thiết để tránh lỗi trôi lệnh khi dùng scanf và fgets.
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Nhập thông tin cho 1 sinh viên (trừ điểm TB và xếp loại).
 */
SV nhapMotSV() {
    SV sv;
    
    printf("  + Nhap MSSV (4 so): ");
    scanf("%4s", sv.mssv);
    
    // Xóa bộ đệm trước khi nhập chuỗi (Họ tên)
    clear_input_buffer(); 
    
    printf("  + Nhap Ho ten: ");
    fgets(sv.hoTen, 50, stdin);
    // Xóa ký tự \n ở cuối chuỗi fgets
    sv.hoTen[strcspn(sv.hoTen, "\n")] = 0; 

    printf("  + Nhap Nhom (A/B): ");
    // Khoảng trắng trước %c rất quan trọng, nó bỏ qua ký tự \n
    scanf(" %c", &sv.nhom); 

    printf("  + Nhap Diem Qua Trinh (0-10): ");
    scanf("%f", &sv.diemQT);

    printf("  + Nhap Diem Kiem Tra (0-10): ");
    scanf("%f", &sv.diemKT);

    printf("  + Nhap Diem Thi (0-10): ");
    scanf("%f", &sv.diemThi);

    // Xóa bộ đệm lần cuối để chuẩn bị cho lần lặp sau
    clear_input_buffer();

    return sv;
}

/**
 * @brief Nhập thông tin cho toàn bộ danh sách n sinh viên.
 */
void nhapDanhSach(SV ds[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n-> Nhap thong tin sinh vien thu %d/%d:\n", i + 1, n);
        ds[i] = nhapMotSV();
    }
}

/**
 * @brief In thông tin 1 sinh viên (đã xử lý) theo hàng của bảng.
 */
void xuatMotSV(SV sv, int stt) {
    // Định dạng các cột cho thẳng hàng
    printf("| %-3d | %-5s | %-25s | %-5c | %-12.1f | %-12.1f | %-10.1f | %-10.2f | %-11s |\n",
           stt, sv.mssv, sv.hoTen, sv.nhom,
           sv.diemQT, sv.diemKT, sv.diemThi,
           sv.diemTB, sv.xepLoai);
}

/**
 * @brief In toàn bộ bảng điểm tổng hợp của lớp (gồm tiêu đề).
 [cite_start]* [cite: 50-56]
 */
void xuatBangDiem(SV ds[], int n) {
    printf("+-----+-------+---------------------------+-------+--------------+--------------+------------+------------+-------------+\n");
    printf("| STT | MSSV  | Ho va Ten                 | Nhom  | D.Qua Trinh  | D.Kiem Tra   | D.Thi      | Diem TB    | Xep Loai    |\n");
    printf("|     |       |                           |       | (20%%)       | (30%%)       | (50%%)     |            |             |\n");
    printf("+-----+-------+---------------------------+-------+--------------+--------------+------------+------------+-------------+\n");
    
    for (int i = 0; i < n; i++) {
        xuatMotSV(ds[i], i + 1);
    }
    
    printf("+-----+-------+---------------------------+-------+--------------+--------------+------------+------------+-------------+\n");
}


// --- 2. Module Xử lý & Thống kê cơ bản (Người 2) ---

/**
 * @brief Tính điểm trung bình cho 1 sinh viên.
 [cite_start]* [cite: 24-26]
 */
float tinhDiemTB(SV sv) {
    // 20%QT + 30%KT + 50%Thi
    return (sv.diemQT * 0.2) + (sv.diemKT * 0.3) + (sv.diemThi * 0.5);
}

/**
 * @brief Trả về chuỗi xếp loại dựa trên điểm TB.
 [cite_start]* [cite: 27-41]
 * *** ĐÂY LÀ PHẦN SỬA LỖI WARNING ***
 */
const char* xepLoai(float diemTB) {
    if (diemTB >= 9.0) return "Xuat sac";
    else if (diemTB >= 8.0) return "Gioi";
    else if (diemTB >= 6.5) return "Kha";
    else if (diemTB >= 5.0) return "Trung binh";
    else return "Khong dat";
}

/**
 * @brief Cập nhật điểm TB và xếp loại cho TOÀN BỘ danh sách.
 * *** ĐÂY LÀ PHẦN SỬA LỖI WARNING ***
 */
void xuLyDanhSach(SV ds[], int n) {
    for (int i = 0; i < n; i++) {
        // 1. Tính điểm TB
        ds[i].diemTB = tinhDiemTB(ds[i]);
        
        // 2. Gán xếp loại
        const char* xl = xepLoai(ds[i].diemTB); // Thêm 'const'
        strcpy(ds[i].xepLoai, xl);
    }
}

/**
 * @brief Tính điểm TB chung của cả lớp.
 */
float tinhDiemTBLop(SV ds[], int n) {
    if (n == 0) return 0.0;

    float tong = 0.0;
    for (int i = 0; i < n; i++) {
        tong += ds[i].diemTB;
    }
    return tong / n;
}

/**
 * @brief Tính điểm TB của một nhóm (A hoặc B).
 */
float tinhDiemTBNhom(SV ds[], int n, char tenNhom) {
    float tong = 0.0;
    int dem = 0;
    
    for (int i = 0; i < n; i++) {
        if (ds[i].nhom == tenNhom) {
            tong += ds[i].diemTB;
            dem++;
        }
    }
    
    if (dem == 0) return 0.0; // Tránh lỗi chia cho 0
    return tong / dem;
}

/**
 * @brief Đếm và in ra số lượng sinh viên theo từng xếp loại.
 [cite_start]* [cite: 62-74]
 */
void thongKeXepLoai(SV ds[], int n) {
    int demXS = 0, demG = 0, demK = 0, demTB = 0, demKD = 0;
    
    for (int i = 0; i < n; i++) {
        // Dùng strcmp để so sánh chuỗi
        if (strcmp(ds[i].xepLoai, "Xuat sac") == 0) demXS++;
        else if (strcmp(ds[i].xepLoai, "Gioi") == 0) demG++;
        else if (strcmp(ds[i].xepLoai, "Kha") == 0) demK++;
        else if (strcmp(ds[i].xepLoai, "Trung binh") == 0) demTB++;
        else if (strcmp(ds[i].xepLoai, "Khong dat") == 0) demKD++;
    }
    
    printf("   + Xuat sac: %d sinh vien\n", demXS);
    printf("   + Gioi:     %d sinh vien\n", demG);
    printf("   + Kha:      %d sinh vien\n", demK);
    printf("   + Trung binh: %d sinh vien\n", demTB);
    printf("   + Khong dat:  %d sinh vien\n", demKD);
}


// --- 3. Module Thống kê Nâng cao (Người 3) ---

/**
 * @brief Tìm điểm TB cao nhất của lớp.
 */
float timDiemCaoNhatLop(SV ds[], int n) {
    if (n == 0) return 0.0;
    
    float maxDiem = ds[0].diemTB;
    for (int i = 1; i < n; i++) {
        if (ds[i].diemTB > maxDiem) {
            maxDiem = ds[i].diemTB;
        }
    }
    return maxDiem;
}

/**
 * @brief Tìm điểm TB thấp nhất của lớp.
 */
float timDiemThapNhatLop(SV ds[], int n) {
    if (n == 0) return 0.0;
    
    float minDiem = ds[0].diemTB;
    for (int i = 1; i < n; i++) {
        if (ds[i].diemTB < minDiem) {
            minDiem = ds[i].diemTB;
        }
    }
    return minDiem;
}

/**
 * @brief Tìm điểm TB cao nhất của một nhóm.
 */
float timDiemCaoNhatNhom(SV ds[], int n, char tenNhom) {
    float maxDiem = -1.0; // Khởi tạo là giá trị không thể
    int daTimThay = 0;
    
    for (int i = 0; i < n; i++) {
        if (ds[i].nhom == tenNhom) {
            if (daTimThay == 0) {
                maxDiem = ds[i].diemTB; // Gán giá trị đầu tiên tìm thấy
                daTimThay = 1;
            } else if (ds[i].diemTB > maxDiem) {
                maxDiem = ds[i].diemTB;
            }
        }
    }
    return (daTimThay == 0) ? 0.0 : maxDiem;
}

/**
 * @brief Tìm điểm TB thấp nhất của một nhóm.
 */
float timDiemThapNhatNhom(SV ds[], int n, char tenNhom) {
    float minDiem = 11.0; // Khởi tạo là giá trị không thể
    int daTimThay = 0;
    
    for (int i = 0; i < n; i++) {
        if (ds[i].nhom == tenNhom) {
            if (daTimThay == 0) {
                minDiem = ds[i].diemTB; // Gán giá trị đầu tiên tìm thấy
                daTimThay = 1;
            } else if (ds[i].diemTB < minDiem) {
                minDiem = ds[i].diemTB;
            }
        }
    }
    return (daTimThay == 0) ? 0.0 : minDiem;
}


/**
 * @brief Hoán vị thông tin của 2 sinh viên (DÙNG CON TRỎ).
 */
void hoanVi(SV* a, SV* b) {
    SV temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Sắp xếp một MẢNG SAO CHÉP theo điểm TB giảm dần.
 * @note Thuật toán: Bubble Sort (Sắp xếp nổi bọt).
 */
void sapXepGiamDan(SV ds_copy[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ds_copy[j].diemTB < ds_copy[j + 1].diemTB) {
                // Hoán vị 2 struct SV
                hoanVi(&ds_copy[j], &ds_copy[j + 1]);
            }
        }
    }
}

/**
 * @brief In ra 3 sinh viên có điểm cao nhất.
 */
void xuatTop3(SV ds[], int n) {
    if (n == 0) return;
    
    // 1. Tạo mảng copy
    SV copy[n];
    for(int i=0; i<n; i++) {
        copy[i] = ds[i];
    }
    
    // 2. Sắp xếp mảng copy
    sapXepGiamDan(copy, n);
    
    // 3. In ra 3 SV đầu tiên (hoặc ít hơn nếu lớp < 3 SV)
    int count = (n < 3) ? n : 3;
    for (int i = 0; i < count; i++) {
        printf("   %d. %s - %s - %.2f diem\n", 
               i + 1, copy[i].mssv, copy[i].hoTen, copy[i].diemTB);
    }
}

/**
 * @brief Sắp xếp một MẢNG SAO CHÉP theo điểm TB tăng dần.
 * @note Thuật toán: Bubble Sort.
 */
void sapXepTangDan(SV ds_copy[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ds_copy[j].diemTB > ds_copy[j + 1].diemTB) {
                // Hoán vị 2 struct SV
                hoanVi(&ds_copy[j], &ds_copy[j + 1]);
            }
        }
    }
}

/**
 * @brief In ra 3 sinh viên có điểm thấp nhất.
 */
void xuatBottom3(SV ds[], int n) {
    if (n == 0) return;
    
    // 1. Tạo mảng copy
    SV copy[n];
    for(int i=0; i<n; i++) {
        copy[i] = ds[i];
    }
    
    // 2. Sắp xếp mảng copy
    sapXepTangDan(copy, n);
    
    // 3. In ra 3 SV đầu tiên (hoặc ít hơn nếu lớp < 3 SV)
    int count = (n < 3) ? n : 3;
    for (int i = 0; i < count; i++) {
        printf("   %d. %s - %s - %.2f diem\n", 
               i + 1, copy[i].mssv, copy[i].hoTen, copy[i].diemTB);
    }
}