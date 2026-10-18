#include <stdio.h>
#include <string.h>

#define MAX_NHAN_VIEN 100

typedef struct {
    int maNV;
    char hoTen[50];
    float luongCoBan;
    int phutMuon;
    float soGioOT;
} NhanVien;

// Khai báo nguyên mẫu hàm
void hienThiMenu();
int timKiemTheoMa(NhanVien ds[], int soLuong, int maNV);
void hienThiDanhSach(NhanVien ds[], int soLuong);
int themNhanVien(NhanVien ds[], int soLuong);
void suaNhanVien(NhanVien ds[], int soLuong);
int xoaNhanVien(NhanVien ds[], int soLuong);

int main() {
    NhanVien ds[MAX_NHAN_VIEN];
    int soLuong = 0;
    int luaChon;

    do {
        hienThiMenu();
        printf("Nhap lua chon: ");
        if (scanf("%d", &luaChon) != 1) {
            printf("Loi: Vui long nhap so hop le!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (luaChon) {
            case 1:
                hienThiDanhSach(ds, soLuong);
                break;
            case 2:
                soLuong = themNhanVien(ds, soLuong);
                break;
            case 3:
                suaNhanVien(ds, soLuong);
                break;
            case 4:
                soLuong = xoaNhanVien(ds, soLuong);
                break;
            case 0:
                printf("Thoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Loi: Lua chon khong hop le. Vui long chon lai!");
        }
    } while (luaChon != 0);

    return 0;
}

void hienThiMenu() {
    printf("\n===== HE THONG QUAN LY NHAN SU HRM =====\n");
    printf("1. Xem danh sach nhan vien & Bang luong\n");
    printf("2. Them nhan vien moi\n");
    printf("3. Cap nhat thong tin nhan vien\n");
    printf("4. Xoa nhan vien\n");
    printf("0. Thoat chuong trinh\n");
    printf("=======================================\n");
}

int timKiemTheoMa(NhanVien ds[], int soLuong, int maNV) {
    for (int i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }
    return -1;
}

void hienThiDanhSach(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\n=> Danh sach nhan vien dang trong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");
    for (int i = 0; i < soLuong; i++) {
        float tienPhat = (ds[i].phutMuon > 15) ? 50000.0f : 0.0f;
        float tienOT = ds[i].soGioOT * (ds[i].luongCoBan / 160.0f) * 1.5f;
        float luongThucNhan = ds[i].luongCoBan + tienOT - tienPhat;

        printf("Ma NV: %d\n", ds[i].maNV);
        printf("Ho ten: %s\n", ds[i].hoTen);
        printf("Luong co ban: %.0f\n", ds[i].luongCoBan);
        printf("Phut muon: %d\n", ds[i].phutMuon);
        printf("Gio OT: %.1f\n", ds[i].soGioOT);
        printf("Tien phat: %.0f\n", tienPhat);
        printf("Tien OT: %.0f\n", tienOT);
        printf("Luong thuc nhan: %.0f\n", luongThucNhan);
        printf("-------------------------\n");
    }
    printf("Tong so nhan vien: %d\n", soLuong);
}

int themNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong >= MAX_NHAN_VIEN) {
        printf("\n=> Loi: Danh sach da day, khong the them moi!\n");
        return soLuong;
    }

    printf("\n--- THEM NHAN VIEN ---\n");
    int maNV;
    printf("Ma NV: ");
    if (scanf("%d", &maNV) != 1) {
        printf("Loi nhap lieu!\n");
        while (getchar() != '\n');
        return soLuong;
    }

    if (maNV <= 0) {
        printf("\n=> Loi: Ma nhan vien phai la so nguyen duong!\n");
        return soLuong;
    }

    if (timKiemTheoMa(ds, soLuong, maNV) != -1) {
        printf("\n=> Loi: Ma nhan vien da ton tai!\n");
        return soLuong;
    }

    ds[soLuong].maNV = maNV;

    while (getchar() != '\n'); // Xoa bo dem

    printf("Ho ten: ");
    fgets(ds[soLuong].hoTen, sizeof(ds[soLuong].hoTen), stdin);
    ds[soLuong].hoTen[strcspn(ds[soLuong].hoTen, "\n")] = 0;

    printf("Luong co ban: ");
    scanf("%f", &ds[soLuong].luongCoBan);

    printf("Phut di muon: ");
    scanf("%d", &ds[soLuong].phutMuon);

    printf("So gio OT: ");
    scanf("%f", &ds[soLuong].soGioOT);

    if (ds[soLuong].luongCoBan < 0 || ds[soLuong].phutMuon < 0 || ds[soLuong].soGioOT < 0) {
        printf("\n=> Loi: Luong, phut muon va gio OT khong duoc am!\n");
        return soLuong;
    }

    printf("\n=> Them nhan vien thanh cong!\n");
    return soLuong + 1;
}

void suaNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\n=> Danh sach nhan vien dang trong!\n");
        return;
    }

    printf("\n--- CAP NHAT THONG TIN NHAN VIEN ---\n");
    int maNV;
    printf("Ma NV can sua: ");
    scanf("%d", &maNV);

    int index = timKiemTheoMa(ds, soLuong, maNV);
    if (index == -1) {
        printf("\n=> Loi: Khong tìm thay ma nhan vien!\n");
        return;
    }

    printf("Nhap luong co ban moi: ");
    scanf("%f", &ds[index].luongCoBan);

    printf("Nhap phut di muon moi: ");
    scanf("%d", &ds[index].phutMuon);

    printf("Nhap so gio OT moi: ");
    scanf("%f", &ds[index].soGioOT);

    if (ds[index].luongCoBan < 0 || ds[index].phutMuon < 0 || ds[index].soGioOT < 0) {
        printf("\n=> Loi: Thong tin nhap vao khong duoc am!\n");
        return;
    }

    printf("\n=> Cap nhat thong tin thanh cong!\n");
}

int xoaNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\n=> Danh sach nhan vien dang trong!\n");
        return soLuong;
    }

    printf("\n--- XOA NHAN VIEN ---\n");
    int maNV;
    printf("Ma NV can xoa: ");
    scanf("%d", &maNV);

    int index = timKiemTheoMa(ds, soLuong, maNV);
    if (index == -1) {
        printf("\n=> Loi: Khong tìm thay ma nhan vien!\n");
        return soLuong;
    }

    for (int i = index; i < soLuong - 1; i++) {
        ds[i] = ds[i + 1];
    }

    printf("\n=> Xoa nhan vien thanh cong!\n");
    return soLuong - 1;
}
