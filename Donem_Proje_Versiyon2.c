#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#define musteriSayisi 100

// İşlev fonksiyonları
void siparisDetaylari(float tekFiyat);

// Ekleme ve Güncelleme Fonksiyonları
void yemek_ekle(int veri, char yemekAdi[25], int miktar, float fiyat);
void fiyat_guncelle();
struct musteriBilgileri musteriEkleme();

// Silme ve Sayma Fonksiyonları
void yemek_sil(int siparisKodu);
void yemek_say();

// Menü fonksiyonları
void yemek_listesi();
void admin_menu();
void siparis_menu();
void ana_menu();
void uygulamayiKapat();
void gecersizGiris();
int secimFonksiyonu();

// Alt menü fonksiyonları
void kebap();
void doner();
void corba();
void evYemekleri();
void balik();
void pizza();
void pide();
void hamburger();
void salata();
void tatli();
void icecekler();

// Tasarım fonksiyonları
void cls();
void echo(char print[]);
void satir_bas(int line);
void tab_bas(int tab);
void bosluk_bas(int space);
void cerceve();
void karsilama();
void ilerleme();

// Kullanılan değişkenler
int kartNo[100];
float karttakiPara[100];
float toplamPara = 1000; // test amaçlı 1000 değeri
unsigned int toplamSiparis[100];
unsigned int siparisMiktari[100];
unsigned int siparis = 0;

// Structların tanımı

struct musteriAdresi
{
    char sehir[25];
    char ilce[25];
    char semt[25];
    char sokak[25];
    char evNo[25];
};

struct krediKartiBilgileri
{ //dosya islemleri ile kredi kart bilgileri sistem icine cekilecek
    char kartNumarasi[16];
    char gecerlilikTarihi[4]; // tarih ay/yıl seklinde
    char kartSahibiAdi[50];
    char guvenlikKodu[3];
};

struct musteriBilgileri
{
    char musteriIsmi[30];
    char musteriSoyismi[30];
    char musteriEMail[40];
    char musteriSifre[15];
    float musteriHesapbakiyesi;
    struct musteriAdresi adres;
    struct krediKartiBilgileri krediKarti;
};

struct iceceklerBilgi
{
    char adi[20];
    int stokAdedi;
    float fiyati;
};

struct kebaplarBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct donerlerBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct hamburgerlerBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct corbalarBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct evYemekleriBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct pizzalarBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct pidelerBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct baliklarBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct salatalarBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct tatlilarBilgi
{
    char adi[20];
    int malzemeAdedi;
    float fiyati;
};

struct Test
{
    char yemekAdi[50];
    int miktar;
    float fiyat;
    int veri;
    struct Test *sonraki;
};

// test tipinde değişken oluşturulması
typedef struct Test test;

test *bas, *liste;

int main()
{
    struct musteriBilgileri musteri[musteriSayisi];

    system("title Marmara Kebap House");
    system("mode con: cols=100 lines=40");
    bas = NULL;

    //yemek_ekle(1, "Adana Kebap  ", 10, 35);

    ilerleme();
    cls();

    karsilama();
    cls();

    ana_menu();
}

void cls()
{
    system("cls");
}

void echo(char print[])
{
    printf("%s", print);
}

void satir_bas(int satir)
{
    int i;
    for (i = 0; i < satir; i++)
    {
        putchar('\n');
    }
}

void tab_bas(int tab)
{
    int i;
    for (i = 0; i < tab; i++)
    {
        putchar('\t');
    }
}

void bosluk_bas(int bosluk)
{
    int i;
    for (i = 0; i < bosluk; i++)
    {
        putchar(' ');
    }
}

void yemek_ekle(int veri, char yemekAdi[25], int miktar, float fiyat)
{
    test *gecici;

    gecici = (test *)malloc(sizeof(test));

    gecici->veri = veri;
    gecici->fiyat = fiyat;

    strcpy(gecici->yemekAdi, yemekAdi);
    gecici->miktar = miktar;
    gecici->sonraki = bas;
    bas = gecici;
    liste = bas;
}

void ana_menu()
{
    cls();

    satir_bas(5);
    tab_bas(3);
    echo("===> [1]. Yemek Listesi");
    Sleep(250);

    satir_bas(2);
    tab_bas(3);
    echo("===> [2]. Admin Paneli");
    Sleep(250);

    satir_bas(2);
    tab_bas(3);
    echo("===> [3]. Yeni Musteri Ekleme Paneli");
    Sleep(250);

    satir_bas(2);
    tab_bas(3);
    echo("===> [4]. Cikis");
    Sleep(150);

    satir_bas(1);

    echo("==> ");
    int anaSecim = secimFonksiyonu();

    switch (anaSecim)
    {
    case 1:
        yemek_listesi();
        break;

    case 2:
        admin_menu();
        break;

    case 3:

        musteriEkleme();
        //musteri[k] = musteriEkleme(); // ? musteri bilgilerinin hangi fonksiyona dondurulecegi kararlastirilmali
        //    k++;
        break;

    case 4:
        uygulamayiKapat();

    default:
        gecersizGiris();
        break;
    }
}

void admin_menu()
{
    cls();
    bosluk_bas(1);
    tab_bas(4);

    printf("==>  [0]. Ana Menu");
    printf("\n\nSifrenizi girin: ");
    int adminSecim = secimFonksiyonu();

    if (adminSecim == 0)
    {
        ana_menu();
    }

    else if (adminSecim != 12345)
    {
        cls();
        bosluk_bas(5);
        tab_bas(4);
        echo("Giris yaparken hatali tuslama yaptiniz...\n\n");
        Sleep(1000);
        ana_menu();
    }

    else if (adminSecim == 12345)
    {
        test *gecici;

        gecici = liste;

        cls();
        bosluk_bas(5);
        tab_bas(4);
        echo("Basariyla giris yaptiniz...\n\n");
        Sleep(1000);

    admin:
        cls();

        bosluk_bas(5);

        tab_bas(4);
        echo("[0]. Ana Menuye Don\n\n");

        tab_bas(4);
        echo("[1]. Gunluk Butce\n\n");

        tab_bas(4);
        echo("[2]. Yemek Ekle\n\n");

        tab_bas(4);
        echo("[3]. Yemek Sil\n\n");

        tab_bas(4);
        echo("[4]. Yemekleri Listele\n\n");

        printf("==> ");
        int adminSecim = secimFonksiyonu();

        switch (adminSecim)
        {
        case 0:
            ana_menu();
            break;

        case 1:
            cls();
            tab_bas(4);
            printf("Kasaya giren toplam para : %0.2f \n", toplamPara);
            getchar();
            Sleep(3000);
            goto admin;
            break;

        case 2:
            cls();
            char yemek[50];
            bosluk_bas(2);
            tab_bas(4);

            printf(" Yemek adini girin: ");
            scanf("%s", &yemek);
            goto admin;
            break;

        case 3:
            cls();
            printf(" Yemek silmek için kodunu girin: ");
            getchar();
            goto admin;
            break;

        case 4:
            cls();
            yemek_listesi();
            getchar();
            Sleep(3000);
            goto admin;
            break;

        default:
            cls();
            puts("Gecersiz giris yaptiniz. Lutfen tekrar deneyiniz. ");
            goto admin;
            break;
        }
    }
}

void yemek_listesi()
{
    system("color 3E");
    printf("\n\t\t");
    system("color 3E");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ana Menu\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [1]. Kebaplar\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [2]. Donerler\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [3]. Hamburgerler\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [4]. Corbalar\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [5]. Ev Yemekleri\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [6]. Pizzalar\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [7]. Pideler\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [8]. Baliklar\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [9]. Salatalar\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [10]. Tatlilar\n\n");
    Sleep(100);

    bosluk_bas(1);
    tab_bas(4);

    echo("==>  [11]. Icecekler\n\n");
    Sleep(100);
    echo("==> ");
    int listeSecim = secimFonksiyonu();

    switch (listeSecim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        kebap();
        break;

    case 2:
        doner();
        break;

    case 3:
        hamburger();
        break;

    case 4:
        corba();
        break;

    case 5:
        evYemekleri();
        break;

    case 6:
        pizza();
        break;

    case 7:
        pide();
        break;

    case 8:
        balik();
        break;

    case 9:
        salata();
        break;

    case 10:
        tatli();
        break;

    case 11:
        icecekler();
        break;

    default:
        cls();
        puts("Gecersiz giris yaptiniz. Lutfen tekrar deneyiniz. ");
        Sleep(250);
        ana_menu();
        break;
    }
}

void icecekler()
{
    int i, icecekCesitSayisi = 7;
    struct iceceklerBilgi icecek[icecekCesitSayisi];

    strcpy(icecek[0].adi, "Kola");
    icecek[0].stokAdedi = 125;
    icecek[0].fiyati = 4.0;

    strcpy(icecek[1].adi, "Fanta");
    icecek[1].stokAdedi = 125;
    icecek[1].fiyati = 4.0;

    strcpy(icecek[2].adi, "Ayran");
    icecek[2].stokAdedi = 125;
    icecek[2].fiyati = 3.0;

    strcpy(icecek[3].adi, "Salgam");
    icecek[3].stokAdedi = 125;
    icecek[3].fiyati = 3.5;

    strcpy(icecek[4].adi, "Soda");
    icecek[4].stokAdedi = 125;
    icecek[4].fiyati = 2.0;

    strcpy(icecek[5].adi, "Turk Kahvesi");
    icecek[5].stokAdedi = 125;
    icecek[5].fiyati = 5.0;

    strcpy(icecek[6].adi, "Su");
    icecek[6].stokAdedi = 125;
    icecek[6].fiyati = 2.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 1F");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ana Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(3);
    for (i = 1; i <= icecekCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, icecek[i - 1].adi, icecek[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int icecek_secim = secimFonksiyonu();

    switch (icecek_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(icecek[0].fiyati);
        break;

    case 2:
        siparisDetaylari(icecek[1].fiyati);
        break;

    case 3:
        siparisDetaylari(icecek[2].fiyati);
        break;

    case 4:
        siparisDetaylari(icecek[3].fiyati);
        break;

    case 5:
        siparisDetaylari(icecek[4].fiyati);
        break;

    case 6:
        siparisDetaylari(icecek[5].fiyati);
        break;

    case 7:
        siparisDetaylari(icecek[6].fiyati);
        break;
    default:
        cls();
        icecekler();
        break;
    }
    Sleep(1000);
    ana_menu();
}

void kebap()
{
    int i, kebapCesitSayisi = 3;
    struct kebaplarBilgi kebap[kebapCesitSayisi];

    strcpy(kebap[0].adi, "Adana");
    kebap[0].malzemeAdedi = 105;
    kebap[0].fiyati = 20.0;

    strcpy(kebap[1].adi, "Urfa");
    kebap[1].malzemeAdedi = 105;
    kebap[1].fiyati = 20.0;

    strcpy(kebap[2].adi, "Alinazik");
    kebap[2].malzemeAdedi = 105;
    kebap[2].fiyati = 25.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= kebapCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, kebap[i - 1].adi, kebap[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int kebap_secim = secimFonksiyonu();

    switch (kebap_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(kebap[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(kebap[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(kebap[2].fiyati);
        icecekler();
        break;

    default:
        cls();
        gecersizGiris();
        break;
    }
}

void doner()
{

    int i, donerCesitSayisi = 3;
    struct donerlerBilgi doner[donerCesitSayisi];

    strcpy(doner[0].adi, "Porsiyon Et Doner");
    doner[0].malzemeAdedi = 100;
    doner[0].fiyati = 27.0;

    strcpy(doner[1].adi, "Pilavustu Et Doner");
    doner[1].malzemeAdedi = 100;
    doner[1].fiyati = 28.0;

    strcpy(doner[2].adi, "Iskender Doner");
    doner[2].malzemeAdedi = 100;
    doner[2].fiyati = 29.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= donerCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, doner[i - 1].adi, doner[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int doner_secim = secimFonksiyonu();

    switch (doner_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(doner[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(doner[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(doner[2].fiyati);
        icecekler();
        break;
    default:
        cls();
        gecersizGiris();
        break;
    }
}

void hamburger()
{
    int i, hamburgerCesitSayisi = 10;
    struct hamburgerlerBilgi hamburger[hamburgerCesitSayisi];

    strcpy(hamburger[0].adi, "Steak Hamburger");
    hamburger[0].malzemeAdedi = 100;
    hamburger[0].fiyati = 10.0;

    strcpy(hamburger[1].adi, "Whopper Hamburger");
    hamburger[1].malzemeAdedi = 100;
    hamburger[1].fiyati = 12.0;

    strcpy(hamburger[2].adi, "Big King Hamburger");
    hamburger[2].malzemeAdedi = 100;
    hamburger[2].fiyati = 15.0;

    strcpy(hamburger[3].adi, "Ekonomik Hamburger");
    hamburger[3].malzemeAdedi = 100;
    hamburger[3].fiyati = 8.0;

    strcpy(hamburger[4].adi, "Marmara Hause Hamburger");
    hamburger[4].malzemeAdedi = 100;
    hamburger[4].fiyati = 15.0;

    strcpy(hamburger[5].adi, "Cheeseburger Hamburger");
    hamburger[5].malzemeAdedi = 100;
    hamburger[5].fiyati = 20.0;

    strcpy(hamburger[6].adi, "King Chicken Hamburger");
    hamburger[6].malzemeAdedi = 100;
    hamburger[6].fiyati = 12.0;

    strcpy(hamburger[7].adi, "Klasik Hamburger");
    hamburger[7].malzemeAdedi = 100;
    hamburger[7].fiyati = 10.0;

    strcpy(hamburger[8].adi, "Gurme Hamburger");
    hamburger[8].malzemeAdedi = 100;
    hamburger[8].fiyati = 20.0;

    strcpy(hamburger[9].adi, "Fish Royale Hamburger");
    hamburger[9].malzemeAdedi = 100;
    hamburger[9].fiyati = 14.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= hamburgerCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, hamburger[i - 1].adi, hamburger[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int hamburger_secim = secimFonksiyonu();

    switch (hamburger_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(hamburger[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(hamburger[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(hamburger[2].fiyati);
        icecekler();
        break;

    case 4:
        siparisDetaylari(hamburger[3].fiyati);
        icecekler();
        break;

    case 5:
        siparisDetaylari(hamburger[4].fiyati);
        icecekler();
        break;

    case 6:
        siparisDetaylari(hamburger[5].fiyati);
        icecekler();
        break;

    case 7:
        siparisDetaylari(hamburger[6].fiyati);
        icecekler();
        break;

    case 8:
        siparisDetaylari(hamburger[7].fiyati);
        icecekler();
        break;

    case 9:
        siparisDetaylari(hamburger[8].fiyati);
        icecekler();
        break;

    case 10:
        siparisDetaylari(hamburger[9].fiyati);
        icecekler();
        break;
    default:
        cls();
        gecersizGiris();
        break;
    }
}

void corba()
{
    int i, corbaCesitSayisi = 10;
    struct corbalarBilgi corba[corbaCesitSayisi];

    strcpy(corba[0].adi, "Mercimek Corbasi");
    corba[0].malzemeAdedi = 105;
    corba[0].fiyati = 8.0;

    strcpy(corba[1].adi, "Tarhana Corbasi");
    corba[1].malzemeAdedi = 105;
    corba[1].fiyati = 9.0;

    strcpy(corba[2].adi, "Iskembe Corbasi");
    corba[2].malzemeAdedi = 105;
    corba[2].fiyati = 13.0;

    strcpy(corba[3].adi, "Ezogelin Corbasi");
    corba[3].malzemeAdedi = 105;
    corba[3].fiyati = 8.0;

    strcpy(corba[4].adi, "Kellepaca Corbasi");
    corba[4].malzemeAdedi = 105;
    corba[4].fiyati = 15.0;

    strcpy(corba[5].adi, "Tavuksuyu Corbasi");
    corba[5].malzemeAdedi = 105;
    corba[5].fiyati = 8.0;

    strcpy(corba[6].adi, "Domates Corbasi");
    corba[6].malzemeAdedi = 105;
    corba[6].fiyati = 8.0;

    strcpy(corba[7].adi, "Yayla Corbasi");
    corba[7].malzemeAdedi = 105;
    corba[7].fiyati = 10.0;

    strcpy(corba[8].adi, "Bamya Corbasi");
    corba[8].malzemeAdedi = 105;
    corba[8].fiyati = 13.0;

    strcpy(corba[9].adi, "Dugun Corbasi");
    corba[9].malzemeAdedi = 105;
    corba[9].fiyati = 10.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= corbaCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, corba[i - 1].adi, corba[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int corba_secim = secimFonksiyonu();

    switch (corba_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(corba[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(corba[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(corba[2].fiyati);
        icecekler();
        break;

    case 4:
        siparisDetaylari(corba[3].fiyati);
        icecekler();
        break;

    case 5:
        siparisDetaylari(corba[4].fiyati);
        icecekler();
        break;

    case 6:
        siparisDetaylari(corba[5].fiyati);
        icecekler();
        break;

    case 7:
        siparisDetaylari(corba[6].fiyati);
        icecekler();
        break;

    case 8:
        siparisDetaylari(corba[7].fiyati);
        icecekler();
        break;

    case 9:
        siparisDetaylari(corba[8].fiyati);
        icecekler();
        break;

    case 10:
        siparisDetaylari(corba[9].fiyati);
        icecekler();
        break;
    default:
        cls();
        gecersizGiris();
        break;
    }
}

void evYemekleri()
{
    int i, evYemekCesitSayisi = 11;
    struct evYemekleriBilgi evYemek[evYemekCesitSayisi];

    strcpy(evYemek[0].adi, "Pilav");
    evYemek[0].malzemeAdedi = 105;
    evYemek[0].fiyati = 10.0;

    strcpy(evYemek[1].adi, "Tavuk Sote");
    evYemek[1].malzemeAdedi = 105;
    evYemek[1].fiyati = 12.0;

    strcpy(evYemek[2].adi, "kori Soslu Tavuk");
    evYemek[2].malzemeAdedi = 105;
    evYemek[2].fiyati = 15.0;

    strcpy(evYemek[3].adi, "Makarna");
    evYemek[3].malzemeAdedi = 105;
    evYemek[3].fiyati = 8.0;

    strcpy(evYemek[4].adi, "Zeytin Yagli Dolma");
    evYemek[4].malzemeAdedi = 105;
    evYemek[4].fiyati = 15.0;

    strcpy(evYemek[5].adi, "Ciger");
    evYemek[5].malzemeAdedi = 105;
    evYemek[5].fiyati = 20.0;

    strcpy(evYemek[6].adi, "Kizarmis Tavuk");
    evYemek[6].malzemeAdedi = 105;
    evYemek[6].fiyati = 12.0;

    strcpy(evYemek[7].adi, "Patates Kizartmasi");
    evYemek[7].malzemeAdedi = 105;
    evYemek[7].fiyati = 10.0;

    strcpy(evYemek[8].adi, "Bulgur Pilavi");
    evYemek[8].malzemeAdedi = 105;
    evYemek[8].fiyati = 10.0;

    strcpy(evYemek[9].adi, "Etli Nohut");
    evYemek[9].malzemeAdedi = 105;
    evYemek[9].fiyati = 14.0;

    strcpy(evYemek[10].adi, "Kofte");
    evYemek[10].malzemeAdedi = 105;
    evYemek[10].fiyati = 20.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= evYemekCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, evYemek[i - 1].adi, evYemek[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int evYemekleri_secim = secimFonksiyonu();

    switch (evYemekleri_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(evYemek[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(evYemek[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(evYemek[2].fiyati);
        icecekler();
        break;

    case 4:
        siparisDetaylari(evYemek[3].fiyati);
        icecekler();
        break;

    case 5:
        siparisDetaylari(evYemek[4].fiyati);
        icecekler();
        break;

    case 6:
        siparisDetaylari(evYemek[5].fiyati);
        icecekler();
        break;

    case 7:
        siparisDetaylari(evYemek[6].fiyati);
        icecekler();
        break;

    case 8:
        siparisDetaylari(evYemek[7].fiyati);
        icecekler();
        break;

    case 9:
        siparisDetaylari(evYemek[8].fiyati);
        icecekler();
        break;

    case 10:
        siparisDetaylari(evYemek[9].fiyati);
        icecekler();
        break;

    case 11:
        siparisDetaylari(evYemek[10].fiyati);
        icecekler();
        break;
    default:
        cls();
        gecersizGiris();
        break;
    }
}

void pizza()
{
    int i, j, pizzaCesitSayisi = 7;
    struct pizzalarBilgi pizza[pizzaCesitSayisi];

    strcpy(pizza[0].adi, "Sucuklu Pizza");
    pizza[0].fiyati = 12.0;
    pizza[0].malzemeAdedi = 105;

    strcpy(pizza[1].adi, "Peynirli Pizza");
    pizza[1].fiyati = 24.0;
    pizza[1].malzemeAdedi = 105;

    strcpy(pizza[2].adi, "Bolbol Pizza");
    pizza[2].fiyati = 32.0;
    pizza[2].malzemeAdedi = 105;

    strcpy(pizza[3].adi, "Meksika Pizza");
    pizza[3].fiyati = 30.0;
    pizza[3].malzemeAdedi = 105;

    strcpy(pizza[4].adi, "Mozarella Pizza");
    pizza[4].fiyati = 35.0;
    pizza[4].malzemeAdedi = 105;

    strcpy(pizza[5].adi, "NewYork Pizza");
    pizza[5].fiyati = 34.0;
    pizza[5].malzemeAdedi = 105;

    strcpy(pizza[6].adi, "MarmaraPizza Pizza");
    pizza[6].fiyati = 17.0;
    pizza[6].malzemeAdedi = 105;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= pizzaCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, pizza[i - 1].adi, pizza[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int pizza_secim = secimFonksiyonu();

    switch (pizza_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(pizza[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(pizza[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(pizza[2].fiyati);
        icecekler();
        break;

    case 4:
        siparisDetaylari(pizza[3].fiyati);
        icecekler();
        break;

    case 5:
        siparisDetaylari(pizza[4].fiyati);
        icecekler();
        break;

    case 6:
        siparisDetaylari(pizza[5].fiyati);
        icecekler();
        break;

    case 7:
        siparisDetaylari(pizza[6].fiyati);
        icecekler();
        break;
    default:
        cls();
        gecersizGiris();
        break;
    }
}

void pide()
{
    int i, pideCesitSayisi = 7;
    struct pidelerBilgi pide[pideCesitSayisi];

    strcpy(pide[0].adi, "Kiymali Pide");
    pide[0].malzemeAdedi = 100;
    pide[0].fiyati = 12.0;

    strcpy(pide[1].adi, "Kavurmali Pide");
    pide[1].malzemeAdedi = 100;
    pide[1].fiyati = 15.0;

    strcpy(pide[2].adi, "kusbasi Pide");
    pide[2].malzemeAdedi = 100;
    pide[2].fiyati = 15.0;

    strcpy(pide[3].adi, "Sucuklu Yumurtali Pide");
    pide[3].malzemeAdedi = 100;
    pide[3].fiyati = 15.0;

    strcpy(pide[4].adi, "Peynirli Pide");
    pide[4].malzemeAdedi = 100;
    pide[4].fiyati = 14.0;

    strcpy(pide[5].adi, "Mevlana Pide");
    pide[5].malzemeAdedi = 100;
    pide[5].fiyati = 18.0;

    strcpy(pide[6].adi, "BicakArasi Pide");
    pide[6].malzemeAdedi = 100;
    pide[6].fiyati = 19.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= pideCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, pide[i - 1].adi, pide[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int pide_secim = secimFonksiyonu();

    switch (pide_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(pide[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(pide[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(pide[2].fiyati);
        icecekler();
        break;

    case 4:
        siparisDetaylari(pide[3].fiyati);
        icecekler();
        break;

    case 5:
        siparisDetaylari(pide[4].fiyati);
        icecekler();
        break;

    case 6:
        siparisDetaylari(pide[5].fiyati);
        icecekler();
        break;

    case 7:
        siparisDetaylari(pide[6].fiyati);
        icecekler();
        break;
    default:
        cls();
        gecersizGiris();
        break;
    }
}

void balik()
{
    int i, balikCesitSayisi = 7;
    struct baliklarBilgi balik[balikCesitSayisi];

    strcpy(balik[0].adi, "Hamsi");
    balik[0].malzemeAdedi = 100;
    balik[0].fiyati = 30.0;

    strcpy(balik[1].adi, "Cipura");
    balik[1].malzemeAdedi = 100;
    balik[1].fiyati = 30.0;

    strcpy(balik[2].adi, "Levrek");
    balik[2].malzemeAdedi = 100;
    balik[2].fiyati = 30.0;

    strcpy(balik[3].adi, "Istavrit");
    balik[3].malzemeAdedi = 100;
    balik[3].fiyati = 30.0;

    strcpy(balik[4].adi, "Kefal");
    balik[4].malzemeAdedi = 100;
    balik[4].fiyati = 30.0;

    strcpy(balik[5].adi, "Istakoz");
    balik[5].malzemeAdedi = 100;
    balik[5].fiyati = 50.0;

    strcpy(balik[6].adi, "Midye");
    balik[6].malzemeAdedi = 100;
    balik[6].fiyati = 1.5;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= balikCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, balik[i - 1].adi, balik[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int balik_secim = secimFonksiyonu();

    switch (balik_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(balik[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(balik[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(balik[2].fiyati);
        icecekler();
        break;

    case 4:
        siparisDetaylari(balik[3].fiyati);
        icecekler();
        break;

    case 5:
        siparisDetaylari(balik[4].fiyati);
        icecekler();
        break;

    case 6:
        siparisDetaylari(balik[5].fiyati);
        icecekler();
        break;

    case 7:
        siparisDetaylari(balik[6].fiyati);
        icecekler();
        break;
    default:
        cls();
        gecersizGiris();
        break;
    }
}

void salata()
{
    int i, salataCesitSayisi = 4;
    struct salatalarBilgi salata[salataCesitSayisi];

    strcpy(salata[0].adi, "Gobek Salata");
    salata[0].malzemeAdedi = 100;
    salata[0].fiyati = 8.0;

    strcpy(salata[1].adi, "Coban Salata");
    salata[1].malzemeAdedi = 100;
    salata[1].fiyati = 10.0;

    strcpy(salata[2].adi, "Mevsim Salatasi");
    salata[2].malzemeAdedi = 100;
    salata[2].fiyati = 7.0;

    strcpy(salata[3].adi, "Patates Salatasi");
    salata[3].malzemeAdedi = 100;
    salata[3].fiyati = 8.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= salataCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, salata[i - 1].adi, salata[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("\n==> ");
    int salata_secim = secimFonksiyonu();

    switch (salata_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(salata[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(salata[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(salata[2].fiyati);
        icecekler();
        break;

    case 4:
        siparisDetaylari(salata[3].fiyati);
        icecekler();
        break;
    default:
        cls();
        gecersizGiris();
        break;
    }
}

void tatli()
{
    int i, tatliCesitSayisi = 9;
    struct tatlilarBilgi tatli[tatliCesitSayisi];

    strcpy(tatli[0].adi, "Kunefe");
    tatli[0].malzemeAdedi = 100;
    tatli[0].fiyati = 13.0;

    strcpy(tatli[1].adi, "Sutlac");
    tatli[1].malzemeAdedi = 100;
    tatli[1].fiyati = 9.0;

    strcpy(tatli[2].adi, "Kadayif");
    tatli[2].malzemeAdedi = 100;
    tatli[2].fiyati = 12.0;

    strcpy(tatli[3].adi, "Baklava");
    tatli[3].malzemeAdedi = 100;
    tatli[3].fiyati = 30.0;

    strcpy(tatli[4].adi, "Trilece");
    tatli[4].malzemeAdedi = 100;
    tatli[4].fiyati = 10.0;

    strcpy(tatli[5].adi, "Hosmerim");
    tatli[5].malzemeAdedi = 100;
    tatli[5].fiyati = 10.0;

    strcpy(tatli[6].adi, "Supangle");
    tatli[6].malzemeAdedi = 100;
    tatli[6].fiyati = 8.0;

    strcpy(tatli[7].adi, "Profiterol");
    tatli[7].malzemeAdedi = 100;
    tatli[7].fiyati = 8.0;

    strcpy(tatli[8].adi, "Cheesecake");
    tatli[8].malzemeAdedi = 100;
    tatli[8].fiyati = 12.0;

    system("color 3E");
    printf("\n\t\t");
    system("color 70");

    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    Sleep(100);

    cerceve();
    satir_bas(2);

    for (i = 1; i <= tatliCesitSayisi; i++)
    {
        bosluk_bas(1);
        tab_bas(4);
        printf("===============>  [%d]. %s: %.2f  <================\n\n", i, tatli[i - 1].adi, tatli[i - 1].fiyati);
        Sleep(100);
    }

    cerceve();
    echo("==> ");
    int tatli_secim = secimFonksiyonu();

    switch (tatli_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(tatli[0].fiyati);
        icecekler();
        break;

    case 2:
        siparisDetaylari(tatli[1].fiyati);
        icecekler();
        break;

    case 3:
        siparisDetaylari(tatli[2].fiyati);
        icecekler();
        break;

    case 4:
        siparisDetaylari(tatli[3].fiyati);
        icecekler();
        break;

    case 5:
        siparisDetaylari(tatli[4].fiyati);
        icecekler();
        break;

    case 6:
        siparisDetaylari(tatli[5].fiyati);
        icecekler();
        break;

    case 7:
        siparisDetaylari(tatli[6].fiyati);
        icecekler();
        break;

    case 8:
        siparisDetaylari(tatli[7].fiyati);
        icecekler();
        break;

    case 9:
        siparisDetaylari(tatli[8].fiyati);
        icecekler();

        break;

    default:
        cls();
        gecersizGiris();
        break;
    }
}

void siparis_menu(int siparis, int miktar, int sip_kodu)
{
    system("color 3E");

    test *gecici;

    gecici = liste;

    while (gecici->veri != siparis)
    {
        gecici = gecici->sonraki;
    }

    if (gecici->veri == siparis)
    {
        system("color 3E");

        printf("\n\t\t");
        system("color 0A");
        printf("\xdb     %d      \xdb    %s  \xdb     %d     \xdb     %d     \xdb", sip_kodu, gecici->yemekAdi, miktar, gecici->miktar);
        system("color 3E");
        printf("\n\t\t");
        int i;

        for (i = 0; i < 65; i++)
        {
            putchar('=');
        }
        Sleep(50);
    }
    system("color 3E");
}

void cerceve()
{
    // Alt çerçevenin yazdırılması
    printf("\n\t\t\t\t");
    int i;
    for (i = 0; i < 63; i++)
    {
        putchar('=');
    }
}

void karsilama()
{
    system("color 2E");

    char hosgeldin[50] = "MARMARA KEBAP SALONUNA HOS GELDINIZ";
    printf("\n\n\n\n\n\t\t\t");
    int i;

    for (i = 0; i < strlen(hosgeldin); i++)
    {
        system("color 2E");

        printf(" %c", hosgeldin[i]);
        Sleep(25);
    }

    system("color 2E");
    printf("\n\n\t\t\t\t ");

    Sleep(500);
}

void ilerleme(void)
{
    int i;
    for (i = 15; i <= 100; i += 10)
    {
        cls();
        system("color 3E");

        printf("\n\n\n\n\n\n\n\t\t\t\t");
        printf("%d Yukleniyor... %% \n\n\t\t", i);

        printf("");
        int j;
        for (j = 0; j < i; j += 2)
        {
            printf("\xdb");
            system("color 3E");
        }
        Sleep(10);

        if (i == 90 || i == 50 || i == 96 || i == 83)
        {
            Sleep(25);
        }
    }
}

struct musteriBilgileri musteriEkleme()
{
    cls();
    bosluk_bas(1);
    tab_bas(4);

    printf("==>  [0]. Ana Menu");
    int musteriEklemeSecim = secimFonksiyonu();
    if (musteriEklemeSecim == 0)
    {
        ana_menu();
    }

    else
    {
        cls();
        bosluk_bas(5);
        tab_bas(4);

        struct musteriBilgileri musteriEkleme;
        echo("--Uyelik olusturmak icin lutfen bilgilerinizi giriniz.--\n - Adiniz: ");
        scanf("%s", &musteriEkleme.musteriIsmi);
        echo(" - Soyadiniz: ");
        scanf("%s", &musteriEkleme.musteriSoyismi);
        echo(" - E-mail adresiniz: ");
        scanf("%s", &musteriEkleme.musteriEMail);
        echo(" - Hesabiniz icin sifre olusturunuz: ");
        scanf("%s", &musteriEkleme.musteriSifre);
        echo(" - Kredi karti numaraniz: ");
        scanf("%s", &musteriEkleme.krediKarti.kartNumarasi);
        echo(" - Kredi karti sahibi adi ve soyadi (bitisik yazilmalidir!!): ");
        scanf("%s", &musteriEkleme.krediKarti.kartSahibiAdi);
        echo(" - Kredi karti son gecerlilik tarihi (ay ve yil bitisik yazilmalidir!!): ");
        scanf("%s", &musteriEkleme.krediKarti.gecerlilikTarihi);
        echo(" - Kredi karti guvenlik numaraniz: ");
        scanf("%s", &musteriEkleme.krediKarti.guvenlikKodu);
        echo(" - Evinizin bulundugu sehir:");
        scanf("%s", &musteriEkleme.adres.sehir);
        echo(" - Ilce: ");
        scanf("%s", &musteriEkleme.adres.ilce);
        echo(" - Semp - Mahalle: ");
        scanf("%s", &musteriEkleme.adres.semt);
        echo(" - Sokak: ");
        scanf("%s", &musteriEkleme.adres.sokak);
        echo(" - Ev NO: ");
        scanf("%s", &musteriEkleme.adres.evNo);
        return musteriEkleme;

        echo("Basariyla yeni musteri kaydi olusturulmustur...\n\n");
        Sleep(250);
        echo("Anasayfaya yonlendiriliyorsunuz...\n\n");
        Sleep(1000);
        ana_menu();
    }
}

void uygulamayiKapat()
{
    cls();
    cerceve();
    puts("\n\t\t\t\tYine bekleriz!!");
    Sleep(500);
    tab_bas(4);
    puts("Program kapatiliyor...\n");
    Sleep(400);
    exit(1);
}

void gecersizGiris()
{
    cls();
    puts("Gecersiz giris yaptiniz. Lutfen tekrar deneyiniz. ");
    Sleep(700);
    ana_menu();
}

//Gerekli if yerlerinde kullanılmak uzere seçim icin fonksiyon
int secimFonksiyonu()
{
    int secim;
    scanf("%d", &secim);
    return secim;
}

void siparisDetaylari(float tekFiyat)
{
    float istenenSayi = 0;
    float toplamFiyat = 0;
    echo("Kac tane/porsiyon istersiniz?\n");
    scanf("%f", &istenenSayi);
    toplamFiyat = istenenSayi * tekFiyat;
    printf("Aldiklariniz %.2f TL tutmustur.\n", toplamFiyat);
    Sleep(600);
    echo("Siparisiniz hazirlaniyor. Diger sayfaya yonlendiriliyorsunuz...");
    Sleep(1000);
    //return toplamFiyat; // ! icecek disi diger fiyatlar ile toplanmasi icin Fiyat geri dondurulmeli
}