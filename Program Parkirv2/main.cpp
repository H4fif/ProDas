#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maks_data 25    //maks banyak data
#define hp 1000   //tarif parkir

using namespace std;

struct dp;
int pilihan, total=0, i;
char op;

struct dp{
       char plat_nomor[10];
       time_t jam_masuk;
       time_t jam_keluar;
       int tarif;
       char keterangan[5];
};
dp data_parkir[maks_data];

//struct tm tm = *localtime(&data_parkir[i].jam_masuk);
//struct tm tk = *localtime(&data_parkir[i].jam_keluar);

void menu_utama();
void kendaraan_masuk();
void kendaraan_keluar();  
void cari_plat();         
void hapus_plat();        
void baca_file();         //belum dibuat
void save_file();         //belum dibuat

void menu_utama()
{
     int j,x;
     bool kosong=false;
     
     system("cls");  
     printf("          DATA PARKIRAN\n");
     /*tampilkan data (dalam bentuk tabel)
     --------------------------------------------------------------
     | NO |  Plat No | Jam Masuk | Jam Keluar | Tarif | Keterangan |
     |    |          |           |            |       |            |
     |    |          |           |            |       |            |
     |    |          |           |            |       |            |
     --------------------------------------------------------------
     */
     
     if (strlen(data_parkir[0].plat_nomor)>2){
           i=0;
           while((strlen(data_parkir[i].plat_nomor)>2) && (i<maks_data))
           {
           struct tm tm = *localtime(&data_parkir[i].jam_masuk);
           struct tm tk = *localtime(&data_parkir[i].jam_keluar);
           //tampilan biasa nanti diubah ke bentuk tabel diatas
           printf("\nNo %d",i+1);
           printf("\nPlat Nomor     : %s",data_parkir[i].plat_nomor);
           printf("\nJam Masuk      : Pukul %d:%d:%d Tanggal ", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mday);
           printf("\nJam Keluar     : ");
           if (data_parkir[i].jam_keluar==0)
           {
              printf("-");
           }
           else{
                printf("Pukul %d:%d:%d Tanggal \n", tk.tm_hour, tk.tm_min, tk.tm_sec, tk.tm_mday);
           };
           printf("\nTarif          : Rp%d,00",data_parkir[i].tarif);
           printf("\nKeterangan     : ",data_parkir[i].keterangan);
           
           total=i;
           printf("\n");
           i++;
           };
     }
     else{//bila data kosong (kondisi FALSE) lalu tampilkan pesan
          kosong=true;
          printf("\nFile kosong!\n");
     };
     
     printf("\n1. Input Kendaraan Masuk");
     printf("\n2. Input Kendaraan Keluar");
     x=2;
     //menu pilihan bila data tidak kosong
     if (kosong!=true)
     {
        printf("\n3. Cari Plat");
        printf("\n4. Hapus Entry");
        x=4;
     };
     printf("\n0. Keluar");
     
     do {
        printf("\nPilihan : "); scanf("%d",&pilihan);
     }while (pilihan>x);
     
     switch (pilihan) {
            case 1: kendaraan_masuk();
                    break;
            case 2: kendaraan_keluar();
                    break;
            case 3: cari_plat();
                    break;
            case 4: hapus_plat();
                    break;
            case 0: printf("\n");
                    system("PAUSE");
                    exit(EXIT_SUCCESS);
            default: printf("Menu tidak tersedia!");
                     break;    
     };          
};

void kendaraan_masuk(){
     int j;
     i=total;
     system("cls");
     printf("     KENDARAAN MASUK");
     do {
        printf("\nPlat Nomor     : "); scanf("%s",&data_parkir[i].plat_nomor);
        strlwr(data_parkir[i].plat_nomor);
        data_parkir[i].jam_masuk = time(NULL);
        data_parkir[i].tarif=0;        
        strcpy(data_parkir[i].keterangan,"-");
        struct tm tm = *localtime(&data_parkir[i].jam_masuk);
        struct tm tk = *localtime(&data_parkir[i].jam_keluar);
        printf("Jam Masuk       : Tanggal %d Pukul %d:%d:%d", tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);        
        printf("\nJam Keluar      : ");
        if (data_parkir[i].jam_keluar==0)
        {
           printf("-");
        }
        else{
             printf("Tanggal %d Pukul %d:%d:%d", tk.tm_mday, tk.tm_hour, tk.tm_min, tk.tm_sec);
        };
        printf("\nTarif          : Rp%d,00",data_parkir[i].tarif);
        printf("\nKeterangan     : ",data_parkir[i].keterangan);
        
        /*pake fungsi save_file() disini!*/
        
        //tanya input ulang
        do{
           printf("\nLanjutkan [y/n]? ");
           scanf("%c",&op);
        }while ((op!='y') && (op!='n'));
     }while (op!='n');
     
     printf("\nKembali ke menu awal\n");
     system("pause");
     menu_utama();
};

void kendaraan_keluar()
{
     char cari[10];
     bool ketemu=false;
     i=0;
     system("cls");
     printf("     KENDARAAN KELUAR");
     do {
        printf("\nPlat Nomor : "); scanf("%s",cari);
        while((ketemu!=true) && (i<maks_data))
        {
             if(strcmp(data_parkir[i].plat_nomor,strlwr(cari))==0)
             {
                 ketemu=true;
             }
             else{
                  i++;
             };
        };
        if (ketemu==true){
           data_parkir[i].jam_keluar = time(NULL);
           struct tm tm = *localtime(&data_parkir[i].jam_masuk);
           struct tm tk = *localtime(&data_parkir[i].jam_keluar);
           printf("\nJam Masuk    : Tanggal %d Pukul %d:%d:%d", tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
           printf("\nJam Keluar   : Tanggal %d Pukul %d:%d:%d", tk.tm_mday, tk.tm_hour, tk.tm_min, tk.tm_sec);
           printf("\nTarif        : %d",data_parkir[i].tarif);
           printf("\nKeterangan   : %s",data_parkir[i].keterangan);
        }
        else{
             printf("Data tidak ditemukan!");
        };
        
        do{
              printf("\nLanjutkan [y/n]? "); scanf("%c",&op);
        }while ((op!='y') && (op!='n'));
     }while (op!='n');
     
     printf("\nKembali ke menu awal\n");
     system("pause");
     menu_utama();
};

void cari_plat()
{
     char cari[10];
     bool ketemu;
     
     system("cls");
     printf("     CARI PLAT");
     do {
        printf("\nPlat Nomor : "); scanf("%s",cari);
        while((ketemu!=true) && (i<maks_data))
        {
             if(strcmp(data_parkir[i].plat_nomor,strlwr(cari))==0)
             {
                 ketemu=true;
             }
             else{
                  i++;
             };
        };
        if (ketemu==true){
           struct tm tm = *localtime(&data_parkir[i].jam_masuk);
           struct tm tk = *localtime(&data_parkir[i].jam_keluar);
           printf("\nJam Masuk   : Tanggal %d Pukul %d:%d:%d", tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
           printf("\nJam Keluar   : Tanggal %d Pukul %d:%d:%d", tk.tm_mday, tk.tm_hour, tk.tm_min, tk.tm_sec);
           printf("\nTarif       : %d",data_parkir[i].tarif);
           printf("\nKeterangan  : %s",data_parkir[i].keterangan);
        }
        else{
             printf("Data tidak ditemukan!");
        };
        
        do{
              printf("\nLanjutkan [y/n]? "); scanf("%c",&op);
        }while ((op!='y') && (op!='n'));
     }while (op!='n');
     
     printf("\nKembali ke menu awal\n");
     system("pause");
     menu_utama();
};

void hapus_plat()
{
     char cari[10];
     bool ketemu;
     
     system("cls");
     printf("     HAPUS PLAT");
     do {
        printf("\nPlat Nomor : "); scanf("%s",cari);
        while((ketemu!=true) && (i<maks_data))
        {
             if(strcmp(data_parkir[i].plat_nomor,strlwr(cari))==0)
             {
                 ketemu=true;
             }
             else{
                  i++;
             };
        };
        if (ketemu==true){
           struct tm tm = *localtime(&data_parkir[i].jam_masuk);
           struct tm tk = *localtime(&data_parkir[i].jam_keluar);
           printf("\nJam Masuk   : Tanggal %d Pukul %d:%d:%d", tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
           printf("\nJam Keluar   : Tanggal %d Pukul %d:%d:%d", tk.tm_mday, tk.tm_hour, tk.tm_min, tk.tm_sec);
           printf("\nTarif       : %d",data_parkir[i].tarif);
           printf("\nKeterangan  : %s",data_parkir[i].keterangan);
           printf("\nHapus data ini? [y/n]"); scanf("%c",&op);
           if (op=='y')
           {
              while((strlen(data_parkir[i].plat_nomor)>2) && (i<maks_data))
              {
                   data_parkir[i].plat_nomor=data_parkir[i+1].plat_nomor
                   data_parkir[i].jam_masuk=data_parkir[i+1].jam_masuk
                   data_parkir[i].jam_keluar=data_parkir[i+1].jam_keluar
                   data_parkir[i].tarif=data_parkir[i+1].tarif;        
                   strcpy(data_parkir[i].keterangan,data_parkir[i+1].tarif); 
              };
           };
        }
        else{
             printf("Data tidak ditemukan!");
        };
        
        do{
              printf("\nLanjutkan [y/n]? "); scanf("%c",&op);
        }while ((op!='y') && (op!='n'));
     }while (op!='n');
     
     printf("\nKembali ke menu awal\n");
     system("pause");
     menu_utama();
};

int main(int argc, char *argv[])
{
    menu_utama();
    
    
    
    printf("\n");
    printf("\n");
    system("PAUSE");
    return EXIT_SUCCESS;
}
