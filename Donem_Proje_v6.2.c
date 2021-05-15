#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
// #include <unistd.h>
#define musteriSayisi 100

//static FILE *fopen(char *musteriKayitlari,char *a); //dosya acildi.

short satir, kolon;

// Kullanılan değişkenler
int kartNo[100];
int fisIslemSayaci = 0;
float karttakiPara[100];
float kasadakiPara = 1000; // test amaçlı 1000 değeri
float toplamTutar = 0.0;
unsigned int toplamSiparis[100];
unsigned int siparisMiktari[100];
unsigned int siparis = 0;

// İşlev fonksiyonları
void siparisDetaylari(float *fiyatToplam, float tekFiyat, char isim[], int fisIslemSayaci);

// Silme ve Sayma Fonksiyonları
void yemek_sil(int siparisKodu);
void yemek_say();

// Menü fonksiyonları
void yemek_listesi(int n);
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
void tamEkran();
void cls();
void echo(char print[]);
void satir_bas(int line);
void tab_bas(int tab);
void bosluk_bas(int space);
void cerceve();
void karsilama();
void ilerleme();
void menuRenk();

// Structlarin tanımı
struct musteriBilgileri
{
    char *musteriIsmi;
    char *musteriSoyismi;
    char *musteriEMail;
    char *musteriSifre;

    float musteriHesapbakiyesi;

    struct musteriAdresi
    {
        char *sehir;
        char *ilce;
        char *semt;
        char *sokak;
        char *daireNo;
    };

    struct krediKartiBilgileri
    {
        char *kartNumarasi;
        char *gecerlilikTarihi; // tarih ay/yıl seklinde
        char *kartSahibiAdi;
        char *guvenlikKodu;
    };

    struct musteriAdresi adres;
    struct krediKartiBilgileri krediKarti;

    struct musteriBilgileri *nextPtr;
};

typedef struct musteriBilgileri musteriler;
typedef musteriler *musterilerPtr;
musterilerPtr musteri = NULL;

// Ekleme ve Güncelleme Fonksiyonları
void yemek_ekle(int veri, char yemekAdi[25], int miktar, float fiyat);
void fiyat_guncelle();
void musteriEkleme(musterilerPtr *ptr);
void musteriKayitlariniGoruntule();

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

struct menuBilgi
{
    struct iceceklerBilgi icecekler[7];
    struct kebaplarBilgi kebap[3];
    struct donerlerBilgi doner[3];
    struct hamburgerlerBilgi hamburger[10];
    struct corbalarBilgi corba[10];
    struct evYemekleriBilgi evYemekleri[11];
    struct pizzalarBilgi pizza[7];
    struct pidelerBilgi pide[7];
    struct baliklarBilgi balik[7];
    struct salatalarBilgi salata[4];
    struct tatlilarBilgi tatli[9];
};
struct menuBilgi Yemek_Menu;

struct Test
{
    char yemekAdi[50];
    int miktar;
    float fiyat;
    int veri;
    struct Test *sonraki;
};

//Structlar - fonksiyon // Yemek Secimi
void kebapSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void kebapBilgisiGuncelleme(struct menuBilgi *ptrYemek_Menu);

void donerSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void hamburgerSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void corbaSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void evYemekleriSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void pizzaSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void pideSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void balikSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void salataSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void tatliSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

void icecekSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n);

// test tipinde değişken oluşturulması
typedef struct Test test;

test *bas, *liste;

int main()
{
    tamEkran(); // Konsol ekranini tam ekran seklinde donusturme
    struct musteriBilgileri musteri[musteriSayisi];
    //struct musteriBilgileri *musteriler;
    system("title Marmara Kebap House");
    //system("mode con: cols=100 lines=40");
    bas = NULL;

    //yemek_ekle(1, "Adana Kebap  ", 10, 35);

    /*
    ilerleme();
    cls();
    karsilama();
    cls();
    */
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

void menuRenk()
{
    //system("color 3E");
    printf("\n\t\t");
    //system("color 3E");
    cls();
    bosluk_bas(1);
    tab_bas(4);
    printf("\n\t\t");
    echo("==>  [0]. Ust Menu\n\n");
    bosluk_bas(2);
    Sleep(35);
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
    int i, n = 0;
    char anaMenuListesi[4][30] = {"Yemek Listesi", "Admin Paneli", "Yeni Musteri Ekleme Paneli", "Cikis"};
    satir_bas(10);
    for (i = 0; i < 4; i++)
    {
        satir_bas(2);
        tab_bas(9);
        printf("==>  [%d]. %s\n\n", i + 1, anaMenuListesi[i]);
        Sleep(100);
    }
    satir_bas(1);

    int anaSecim = secimFonksiyonu();
    switch (anaSecim)
    {
    case 1:
        yemek_listesi(n);
        break;

    case 2:
        admin_menu();
        break;

    case 3:
        //musteriEkleme(musteri);
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
    menuRenk();
    echo("\n\nSifrenizi girin: ");
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
        satir_bas(10);
        tab_bas(9);
        echo("Basariyla giris yaptiniz...\n\n");
        Sleep(1000);

    admin:
        cls();
        bosluk_bas(5);

        int i;
        char adminMenuListesi[6][40] = {"Ana Menuye Don", "Gunluk Butce", "Yemek Ekle", "Yemek Sil", "Kayitli Kullanicilar", "Yemekleri Listele"};
        satir_bas(6);
        for (i = 0; i < 6; i++)
        {
            satir_bas(2);
            tab_bas(9);
            printf("==>  [%d]. %s\n\n", i, adminMenuListesi[i]);
            Sleep(100);
        }

        int adminSecim = secimFonksiyonu();
        switch (adminSecim)
        {
        case 0:
            ana_menu();
            break;

        case 1:
            cls();
            satir_bas(8);
            cerceve();
            satir_bas(2);
            tab_bas(8);
            printf("Kasaya giren toplam para : %0.2f \n", kasadakiPara);
            satir_bas(2);
            cerceve();
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
            printf(" Yemek silmek icin kodunu girin: ");
            getchar();
            goto admin;
            break;

        case 4:
            cls();
            musteriKayitlariniGoruntule();
            goto admin;
            break;

        case 5:
            cls();
            int n;
            yemek_listesi(n);
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

void yemek_listesi(int n)
{
    int i;

    char yemekListesi[11][15] = {"Kebaplar", "Donerler", "Hamburgerler", "Corbalar", "Ev Yemekleri",
                                 "Pizzalar", "Pideler", "Baliklar", "Salatalar", "Tatlilar", "Icecekler"};

    menuRenk();
    for (i = 0; i < 11; i++)
    {
        bosluk_bas(1);
        tab_bas(9);
        Sleep(100);
        printf("==>  [%d]. %s\n\n", i + 1, yemekListesi[i]);
    }
    Sleep(100);

    int listeSecim = secimFonksiyonu();

    switch (listeSecim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        kebap(n);
        break;

    case 2:
        doner(n);
        break;

    case 3:
        hamburger(n);
        break;

    case 4:
        corba(n);
        break;

    case 5:
        evYemekleri(n);
        break;

    case 6:
        pizza(n);
        break;

    case 7:
        pide(n);
        break;

    case 8:
        balik(n);
        break;

    case 9:
        salata(n);
        break;

    case 10:
        tatli(n);
        break;

    case 11:
        icecekler(n);
        break;

    default:
        gecersizGiris();
        break;
    }
}

void icecekler(int n)
{
    int i, icecekCesitSayisi = 7;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.icecekler[0].adi, "Kola");
    Yemek_Menu.icecekler[0].stokAdedi = 125;
    Yemek_Menu.icecekler[0].fiyati = 4.0;

    strcpy(Yemek_Menu.icecekler[1].adi, "Fanta");
    Yemek_Menu.icecekler[1].stokAdedi = 125;
    Yemek_Menu.icecekler[1].fiyati = 4.0;

    strcpy(Yemek_Menu.icecekler[2].adi, "Ayran");
    Yemek_Menu.icecekler[2].stokAdedi = 125;
    Yemek_Menu.icecekler[2].fiyati = 3.0;

    strcpy(Yemek_Menu.icecekler[3].adi, "Salgam");
    Yemek_Menu.icecekler[3].stokAdedi = 125;
    Yemek_Menu.icecekler[3].fiyati = 3.5;

    strcpy(Yemek_Menu.icecekler[4].adi, "Soda");
    Yemek_Menu.icecekler[4].stokAdedi = 125;
    Yemek_Menu.icecekler[4].fiyati = 2.0;

    strcpy(Yemek_Menu.icecekler[5].adi, "Turk Kahvesi");
    Yemek_Menu.icecekler[5].stokAdedi = 125;
    Yemek_Menu.icecekler[5].fiyati = 5.0;

    strcpy(Yemek_Menu.icecekler[6].adi, "Su");
    Yemek_Menu.icecekler[6].stokAdedi = 125;
    Yemek_Menu.icecekler[6].fiyati = 2.0;

    menuRenk();
    cerceve();
    satir_bas(3);
    for (i = 1; i <= icecekCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("==================>  [%d].%10s: %5.2f%25s", i, Yemek_Menu.icecekler[i - 1].adi, Yemek_Menu.icecekler[i - 1].fiyati, "<==================\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
        Sleep(1000);
    }
    else
    {
        icecekSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void icecekSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");
    fisIslemSayaci = 3;
    int icecek_secim = secimFonksiyonu();
    switch (icecek_secim)
    {
    case 0:
        echo("Icecek istemediginizden emin misiniz? Evet 1 / Hayir 0 \n");
        int tercih = secimFonksiyonu();
        if (tercih)
        {
            //!Buraya ekstradan fis sonlandirma kismi eklenmeli ya da bu kısım kaldırılmalı
            printf("Aldiklariniz %.2f TL tutmustur.\n", toplamTutar);
            echo("Siparisiniz hazirlaniyor.Anasayfaya yonlendiriliyorsunuz...");
            Sleep(1100);
            kasadakiPara += toplamTutar;
            //TODO:  toplamTutar sifirlanmadan once dosyaya aktarilmali
            toplamTutar = 0;
            ana_menu();
        }
        else
        {
            icecekler(n);
        }
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->icecekler[0].fiyati, ptrYemek_Menu->icecekler[0].adi, fisIslemSayaci);
        kasadakiPara += toplamTutar; //Kasadaki ana para admin panelinden gorulebilir haldedir.
        //TODO: toplamTutar sifirlanmadan once dosyaya aktarilmali
        //! fis yazdırma isleminde icecek ile fisin sonlanacagı if ile düzenlenmeli
        toplamTutar = 0;
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->icecekler[1].fiyati, ptrYemek_Menu->icecekler[1].adi, fisIslemSayaci);
        kasadakiPara += toplamTutar;
        //TODO: toplamTutar sifirlanmadan once dosyaya aktarilmali
        toplamTutar = 0;
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->icecekler[2].fiyati, ptrYemek_Menu->icecekler[2].adi, fisIslemSayaci);
        kasadakiPara += toplamTutar;
        //TODO: toplamTutar sifirlanmadan once dosyaya aktarilmali
        toplamTutar = 0;
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->icecekler[3].fiyati, ptrYemek_Menu->icecekler[3].adi, fisIslemSayaci);
        kasadakiPara += toplamTutar;
        //TODO: toplamTutar sifirlanmadan once dosyaya aktarilmali
        toplamTutar = 0;
        break;

    case 5:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->icecekler[4].fiyati, ptrYemek_Menu->icecekler[4].adi, fisIslemSayaci);
        kasadakiPara += toplamTutar;
        //TODO: toplamTutar sifirlanmadan once dosyaya aktarilmali
        toplamTutar = 0;
        break;

    case 6:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->icecekler[5].fiyati, ptrYemek_Menu->icecekler[5].adi, fisIslemSayaci);
        kasadakiPara += toplamTutar;
        //TODO: toplamTutar sifirlanmadan once dosyaya aktarilmali
        toplamTutar = 0;
        break;

    case 7:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->icecekler[6].fiyati, ptrYemek_Menu->icecekler[6].adi, fisIslemSayaci);
        kasadakiPara += toplamTutar;
        //TODO: toplamTutar sifirlanmadan once dosyaya aktarilmali
        toplamTutar = 0;
        break;
    default:
        cls();
        icecekler(n);
        break;
    }
    Sleep(1000);
    fisIslemSayaci = 0;
    ana_menu();
}

void kebap(int n)
{
    int i, kebapCesitSayisi = 3;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.kebap[0].adi, "Adana");
    Yemek_Menu.kebap[0].malzemeAdedi = 105;
    Yemek_Menu.kebap[0].fiyati = 20.0;

    strcpy(Yemek_Menu.kebap[1].adi, "Urfa");
    Yemek_Menu.kebap[1].malzemeAdedi = 105;
    Yemek_Menu.kebap[1].fiyati = 20.0;

    strcpy(Yemek_Menu.kebap[2].adi, "Alinazik");
    Yemek_Menu.kebap[2].malzemeAdedi = 105;
    Yemek_Menu.kebap[2].fiyati = 25.0;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= kebapCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("=========================>  [%d].%10s: %5.2f%25s  ", i, Yemek_Menu.kebap[i - 1].adi, Yemek_Menu.kebap[i - 1].fiyati, "<=========================\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        kebapBilgisiGuncelleme(ptrYemek_Menu);
        //TODO: admin yemek guncelleme fonksiyonu gelistirilmeli
    }
    else
    {
        kebapSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void kebapBilgisiGuncelleme(struct menuBilgi *ptrYemek_Menu)
{
    int kebapGuncelleme;
    echo("\n\nGuncellemek istediginiz yemegin numarasini giriniz.\n");

hataliTuslama:

    kebapGuncelleme = secimFonksiyonu();

    switch (kebapGuncelleme)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        printf("\n%s yemeginin yeni ismini giriniz: ", *ptrYemek_Menu->kebap[0].adi);
        scanf("%s", &ptrYemek_Menu->kebap[0].adi);
        printf("\n Yemeginin yeni ismi: %s ", *ptrYemek_Menu->kebap[0].adi);
        break;
        /*
    case 2:
        break;
    case 3:
        break;
*/
    default:
        cls();
        puts("Gecersiz giris yaptiniz. Lutfen tekrar deneyiniz. ");
        goto hataliTuslama;
        break;
    }
    echo("\n Basariyla kaydedilmistir.");
    getch();
    ana_menu();
}

void kebapSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");
    int kebap_secim = secimFonksiyonu();

    switch (kebap_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->kebap[0].fiyati, ptrYemek_Menu->kebap[0].adi, fisIslemSayaci); // 0
        fisIslemSayaci++;
        salata(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->kebap[1].fiyati, ptrYemek_Menu->kebap[1].adi, fisIslemSayaci); // 0
        fisIslemSayaci++;
        salata(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->kebap[2].fiyati, ptrYemek_Menu->kebap[2].adi, fisIslemSayaci); // 0
        fisIslemSayaci++;
        salata(n);
        break;

    default:
        cls();
        gecersizGiris();
        break;
    }
}

void doner(int n)
{
    int i, donerCesitSayisi = 3;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.doner[0].adi, "Porsiyon Et Doner");
    Yemek_Menu.doner[0].malzemeAdedi = 100;
    Yemek_Menu.doner[0].fiyati = 27.0;

    strcpy(Yemek_Menu.doner[1].adi, "Pilavustu Et Doner");
    Yemek_Menu.doner[1].malzemeAdedi = 100;
    Yemek_Menu.doner[1].fiyati = 28.0;

    strcpy(Yemek_Menu.doner[2].adi, "Iskender Doner");
    Yemek_Menu.doner[2].malzemeAdedi = 100;
    Yemek_Menu.doner[2].fiyati = 29.0;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= donerCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("==================>  [%d].%20s: %5.2f%25s  ", i, Yemek_Menu.doner[i - 1].adi, Yemek_Menu.doner[i - 1].fiyati, "<==================\n\n");
        Sleep(100);
    }

    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        donerSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void donerSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");
    int doner_secim = secimFonksiyonu();

    switch (doner_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->doner[0].fiyati, ptrYemek_Menu->doner[0].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->doner[1].fiyati, ptrYemek_Menu->doner[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->doner[2].fiyati, ptrYemek_Menu->doner[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;
    default:
        gecersizGiris();
        break;
    }
}

void hamburger(int n)
{
    int i, hamburgerCesitSayisi = 10;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.hamburger[0].adi, "Steak Hamburger");
    Yemek_Menu.hamburger[0].malzemeAdedi = 100;
    Yemek_Menu.hamburger[0].fiyati = 10.0;

    strcpy(Yemek_Menu.hamburger[1].adi, "Whopper Hamburger");
    Yemek_Menu.hamburger[1].malzemeAdedi = 100;
    Yemek_Menu.hamburger[1].fiyati = 12.0;

    strcpy(Yemek_Menu.hamburger[2].adi, "Big King Hamburger");
    Yemek_Menu.hamburger[2].malzemeAdedi = 100;
    Yemek_Menu.hamburger[2].fiyati = 15.0;

    strcpy(Yemek_Menu.hamburger[3].adi, "Ekonomik Hamburger");
    Yemek_Menu.hamburger[3].malzemeAdedi = 100;
    Yemek_Menu.hamburger[3].fiyati = 8.0;

    strcpy(Yemek_Menu.hamburger[4].adi, "Marmara Hause Hamburger");
    Yemek_Menu.hamburger[4].malzemeAdedi = 100;
    Yemek_Menu.hamburger[4].fiyati = 15.0;

    strcpy(Yemek_Menu.hamburger[5].adi, "Cheeseburger Hamburger");
    Yemek_Menu.hamburger[5].malzemeAdedi = 100;
    Yemek_Menu.hamburger[5].fiyati = 20.0;

    strcpy(Yemek_Menu.hamburger[6].adi, "King Chicken Hamburger");
    Yemek_Menu.hamburger[6].malzemeAdedi = 100;
    Yemek_Menu.hamburger[6].fiyati = 12.0;

    strcpy(Yemek_Menu.hamburger[7].adi, "Klasik Hamburger");
    Yemek_Menu.hamburger[7].malzemeAdedi = 100;
    Yemek_Menu.hamburger[7].fiyati = 10.0;

    strcpy(Yemek_Menu.hamburger[8].adi, "Gurme Hamburger");
    Yemek_Menu.hamburger[8].malzemeAdedi = 100;
    Yemek_Menu.hamburger[8].fiyati = 20.0;

    strcpy(Yemek_Menu.hamburger[9].adi, "Fish Royale Hamburger");
    Yemek_Menu.hamburger[9].malzemeAdedi = 100;
    Yemek_Menu.hamburger[9].fiyati = 14.0;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= hamburgerCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("==============>  [%d].%28s: %5.2f %25s", i, Yemek_Menu.hamburger[i - 1].adi, Yemek_Menu.hamburger[i - 1].fiyati, "<==============\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        hamburgerSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void hamburgerSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");
    int hamburger_secim = secimFonksiyonu();

    switch (hamburger_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[0].fiyati, ptrYemek_Menu->hamburger[0].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[1].fiyati, ptrYemek_Menu->hamburger[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[2].fiyati, ptrYemek_Menu->hamburger[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[3].fiyati, ptrYemek_Menu->hamburger[3].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 5:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[4].fiyati, ptrYemek_Menu->hamburger[4].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 6:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[5].fiyati, ptrYemek_Menu->hamburger[5].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 7:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[6].fiyati, ptrYemek_Menu->hamburger[6].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 8:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[7].fiyati, ptrYemek_Menu->hamburger[7].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 9:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[8].fiyati, ptrYemek_Menu->hamburger[8].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 10:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->hamburger[9].fiyati, ptrYemek_Menu->hamburger[9].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;
    default:
        gecersizGiris();
        break;
    }
}

void corba(int n)
{
    int i, corbaCesitSayisi = 10;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.corba[0].adi, "Mercimek Corbasi");
    Yemek_Menu.corba[0].malzemeAdedi = 105;
    Yemek_Menu.corba[0].fiyati = 8.0;

    strcpy(Yemek_Menu.corba[1].adi, "Tarhana Corbasi");
    Yemek_Menu.corba[1].malzemeAdedi = 105;
    Yemek_Menu.corba[1].fiyati = 9.0;

    strcpy(Yemek_Menu.corba[2].adi, "Iskembe Corbasi");
    Yemek_Menu.corba[2].malzemeAdedi = 105;
    Yemek_Menu.corba[2].fiyati = 13.0;

    strcpy(Yemek_Menu.corba[3].adi, "Ezogelin Corbasi");
    Yemek_Menu.corba[3].malzemeAdedi = 105;
    Yemek_Menu.corba[3].fiyati = 8.0;

    strcpy(Yemek_Menu.corba[4].adi, "Kellepaca Corbasi");
    Yemek_Menu.corba[4].malzemeAdedi = 105;
    Yemek_Menu.corba[4].fiyati = 15.0;

    strcpy(Yemek_Menu.corba[5].adi, "Tavuksuyu Corbasi");
    Yemek_Menu.corba[5].malzemeAdedi = 105;
    Yemek_Menu.corba[5].fiyati = 8.0;

    strcpy(Yemek_Menu.corba[6].adi, "Domates Corbasi");
    Yemek_Menu.corba[6].malzemeAdedi = 105;
    Yemek_Menu.corba[6].fiyati = 8.0;

    strcpy(Yemek_Menu.corba[7].adi, "Yayla Corbasi");
    Yemek_Menu.corba[7].malzemeAdedi = 105;
    Yemek_Menu.corba[7].fiyati = 10.0;

    strcpy(Yemek_Menu.corba[8].adi, "Bamya Corbasi");
    Yemek_Menu.corba[8].malzemeAdedi = 105;
    Yemek_Menu.corba[8].fiyati = 13.0;

    strcpy(Yemek_Menu.corba[9].adi, "Dugun Corbasi");
    Yemek_Menu.corba[9].malzemeAdedi = 105;
    Yemek_Menu.corba[9].fiyati = 10.0;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= corbaCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("==================>  [%d].%20s: %5.2f%25s   ", i, Yemek_Menu.corba[i - 1].adi, Yemek_Menu.corba[i - 1].fiyati, "<==================\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        corbaSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void corbaSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");
    int corba_secim = secimFonksiyonu();

    switch (corba_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[0].fiyati, ptrYemek_Menu->corba[0].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[1].fiyati, ptrYemek_Menu->corba[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[2].fiyati, ptrYemek_Menu->corba[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[3].fiyati, ptrYemek_Menu->corba[3].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 5:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[4].fiyati, ptrYemek_Menu->corba[4].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 6:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[5].fiyati, ptrYemek_Menu->corba[5].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 7:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[6].fiyati, ptrYemek_Menu->corba[6].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 8:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[7].fiyati, ptrYemek_Menu->corba[7].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 9:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[8].fiyati, ptrYemek_Menu->corba[8].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 10:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->corba[9].fiyati, ptrYemek_Menu->corba[9].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;
    default:
        gecersizGiris();
        break;
    }
}

void evYemekleri(int n)
{
    int i, evYemekCesitSayisi = 11;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.evYemekleri[0].adi, "Pilav");
    Yemek_Menu.evYemekleri[0].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[0].fiyati = 10.0;

    strcpy(Yemek_Menu.evYemekleri[1].adi, "Tavuk Sote");
    Yemek_Menu.evYemekleri[1].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[1].fiyati = 12.0;

    strcpy(Yemek_Menu.evYemekleri[2].adi, "kori Soslu Tavuk");
    Yemek_Menu.evYemekleri[2].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[2].fiyati = 15.0;

    strcpy(Yemek_Menu.evYemekleri[3].adi, "Makarna");
    Yemek_Menu.evYemekleri[3].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[3].fiyati = 8.0;

    strcpy(Yemek_Menu.evYemekleri[4].adi, "Zeytin Yagli Dolma");
    Yemek_Menu.evYemekleri[4].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[4].fiyati = 15.0;

    strcpy(Yemek_Menu.evYemekleri[5].adi, "Ciger");
    Yemek_Menu.evYemekleri[5].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[5].fiyati = 20.0;

    strcpy(Yemek_Menu.evYemekleri[6].adi, "Kizarmis Tavuk");
    Yemek_Menu.evYemekleri[6].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[6].fiyati = 12.0;

    strcpy(Yemek_Menu.evYemekleri[7].adi, "Patates Kizartmasi");
    Yemek_Menu.evYemekleri[7].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[7].fiyati = 10.0;

    strcpy(Yemek_Menu.evYemekleri[8].adi, "Bulgur Pilavi");
    Yemek_Menu.evYemekleri[8].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[8].fiyati = 10.0;

    strcpy(Yemek_Menu.evYemekleri[9].adi, "Etli Nohut");
    Yemek_Menu.evYemekleri[9].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[9].fiyati = 14.0;

    strcpy(Yemek_Menu.evYemekleri[10].adi, "Kofte");
    Yemek_Menu.evYemekleri[10].malzemeAdedi = 105;
    Yemek_Menu.evYemekleri[10].fiyati = 20.0;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= evYemekCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("=======================>  [%d].%20s: %5.2f%25s", i, Yemek_Menu.evYemekleri[i - 1].adi, Yemek_Menu.evYemekleri[i - 1].fiyati, "<=======================\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        evYemekleriSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void evYemekleriSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");
    int evYemekleri_secim = secimFonksiyonu();

    switch (evYemekleri_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[0].fiyati, ptrYemek_Menu->evYemekleri[0].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[1].fiyati, ptrYemek_Menu->evYemekleri[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[2].fiyati, ptrYemek_Menu->evYemekleri[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[3].fiyati, ptrYemek_Menu->evYemekleri[3].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 5:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[4].fiyati, ptrYemek_Menu->evYemekleri[4].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 6:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[5].fiyati, ptrYemek_Menu->evYemekleri[5].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 7:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[6].fiyati, ptrYemek_Menu->evYemekleri[6].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 8:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[7].fiyati, ptrYemek_Menu->evYemekleri[7].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 9:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[8].fiyati, ptrYemek_Menu->evYemekleri[8].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 10:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[9].fiyati, ptrYemek_Menu->evYemekleri[9].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 11:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->evYemekleri[10].fiyati, ptrYemek_Menu->evYemekleri[10].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;
    default:
        gecersizGiris();
        break;
    }
}

void pizza(int n)
{
    int i, pizzaCesitSayisi = 7;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.pizza[0].adi, "Sucuklu Pizza");
    Yemek_Menu.pizza[0].fiyati = 12.0;
    Yemek_Menu.pizza[0].malzemeAdedi = 105;

    strcpy(Yemek_Menu.pizza[1].adi, "Peynirli Pizza");
    Yemek_Menu.pizza[1].fiyati = 24.0;
    Yemek_Menu.pizza[1].malzemeAdedi = 105;

    strcpy(Yemek_Menu.pizza[2].adi, "Bolbol Pizza");
    Yemek_Menu.pizza[2].fiyati = 32.0;
    Yemek_Menu.pizza[2].malzemeAdedi = 105;

    strcpy(Yemek_Menu.pizza[3].adi, "Meksika Pizza");
    Yemek_Menu.pizza[3].fiyati = 30.0;
    Yemek_Menu.pizza[3].malzemeAdedi = 105;

    strcpy(Yemek_Menu.pizza[4].adi, "Mozarella Pizza");
    Yemek_Menu.pizza[4].fiyati = 35.0;
    Yemek_Menu.pizza[4].malzemeAdedi = 105;

    strcpy(Yemek_Menu.pizza[5].adi, "NewYork Pizza");
    Yemek_Menu.pizza[5].fiyati = 34.0;
    Yemek_Menu.pizza[5].malzemeAdedi = 105;

    strcpy(Yemek_Menu.pizza[6].adi, "MarmaraPizza Pizza");
    Yemek_Menu.pizza[6].fiyati = 17.0;
    Yemek_Menu.pizza[6].malzemeAdedi = 105;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= pizzaCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("=======================>  [%d].%20s: %5.2f%25s", i, Yemek_Menu.pizza[i - 1].adi, Yemek_Menu.pizza[i - 1].fiyati, "<=======================\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        pizzaSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void pizzaSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");
    int pizza_secim = secimFonksiyonu();

    switch (pizza_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pizza[0].fiyati, ptrYemek_Menu->pizza[0].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pizza[1].fiyati, ptrYemek_Menu->pizza[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pizza[2].fiyati, ptrYemek_Menu->pizza[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pizza[3].fiyati, ptrYemek_Menu->pizza[3].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 5:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pizza[4].fiyati, ptrYemek_Menu->pizza[4].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 6:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pizza[5].fiyati, ptrYemek_Menu->pizza[5].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 7:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pizza[6].fiyati, ptrYemek_Menu->pizza[6].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;
    default:
        gecersizGiris();
        break;
    }
}

void pide(int n)
{
    int i, pideCesitSayisi = 7;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.pide[0].adi, "Kiymali Pide");
    Yemek_Menu.pide[0].malzemeAdedi = 100;
    Yemek_Menu.pide[0].fiyati = 12.0;

    strcpy(Yemek_Menu.pide[1].adi, "Kavurmali Pide");
    Yemek_Menu.pide[1].malzemeAdedi = 100;
    Yemek_Menu.pide[1].fiyati = 15.0;

    strcpy(Yemek_Menu.pide[2].adi, "Kusbasi Pide");
    Yemek_Menu.pide[2].malzemeAdedi = 100;
    Yemek_Menu.pide[2].fiyati = 15.0;

    strcpy(Yemek_Menu.pide[3].adi, "Sucuklu Yumurtali Pide");
    Yemek_Menu.pide[3].malzemeAdedi = 100;
    Yemek_Menu.pide[3].fiyati = 15.0;

    strcpy(Yemek_Menu.pide[4].adi, "Peynirli Pide");
    Yemek_Menu.pide[4].malzemeAdedi = 100;
    Yemek_Menu.pide[4].fiyati = 14.0;

    strcpy(Yemek_Menu.pide[5].adi, "Mevlana Pide");
    Yemek_Menu.pide[5].malzemeAdedi = 100;
    Yemek_Menu.pide[5].fiyati = 18.0;

    strcpy(Yemek_Menu.pide[6].adi, "Bicak Arasi Pide");
    Yemek_Menu.pide[6].malzemeAdedi = 100;
    Yemek_Menu.pide[6].fiyati = 19.0;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= pideCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("==================>  [%d].%25s: %5.2f%25s", i, Yemek_Menu.pide[i - 1].adi, Yemek_Menu.pide[i - 1].fiyati, "<==================\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        pideSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void pideSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");
    int pide_secim = secimFonksiyonu();

    switch (pide_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pide[0].fiyati, ptrYemek_Menu->pide[0].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pide[1].fiyati, ptrYemek_Menu->pide[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pide[2].fiyati, ptrYemek_Menu->pide[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pide[3].fiyati, ptrYemek_Menu->pide[3].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 5:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pide[4].fiyati, ptrYemek_Menu->pide[4].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 6:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pide[5].fiyati, ptrYemek_Menu->pide[5].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 7:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->pide[6].fiyati, ptrYemek_Menu->pide[6].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;
    default:
        gecersizGiris();
        break;
    }
}

void balik(int n)
{
    int i, balikCesitSayisi = 7;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.balik[0].adi, "Hamsi");
    Yemek_Menu.balik[0].malzemeAdedi = 100;
    Yemek_Menu.balik[0].fiyati = 30.0;

    strcpy(Yemek_Menu.balik[1].adi, "Cipura");
    Yemek_Menu.balik[1].malzemeAdedi = 100;
    Yemek_Menu.balik[1].fiyati = 30.0;

    strcpy(Yemek_Menu.balik[2].adi, "Levrek");
    Yemek_Menu.balik[2].malzemeAdedi = 100;
    Yemek_Menu.balik[2].fiyati = 30.0;

    strcpy(Yemek_Menu.balik[3].adi, "Istavrit");
    Yemek_Menu.balik[3].malzemeAdedi = 100;
    Yemek_Menu.balik[3].fiyati = 30.0;

    strcpy(Yemek_Menu.balik[4].adi, "Kefal");
    Yemek_Menu.balik[6].malzemeAdedi = 100;
    Yemek_Menu.balik[4].fiyati = 30.0;

    strcpy(Yemek_Menu.balik[5].adi, "Istakoz");
    Yemek_Menu.balik[5].malzemeAdedi = 100;
    Yemek_Menu.balik[5].fiyati = 50.0;

    strcpy(Yemek_Menu.balik[6].adi, "Midye");
    Yemek_Menu.balik[6].malzemeAdedi = 100;
    Yemek_Menu.balik[6].fiyati = 1.5;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= balikCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("==========================>  [%d].%10s: %5.2f     %25s   ", i, Yemek_Menu.balik[i - 1].adi, Yemek_Menu.balik[i - 1].fiyati, "<========================\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        balikSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void balikSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
    echo("\n");

    int balik_secim = secimFonksiyonu();
    switch (balik_secim)
    {
    case 0:
        ana_menu();
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->balik[0].fiyati, ptrYemek_Menu->balik[0].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->balik[1].fiyati, ptrYemek_Menu->balik[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->balik[2].fiyati, ptrYemek_Menu->balik[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->balik[3].fiyati, ptrYemek_Menu->balik[3].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 5:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->balik[4].fiyati, ptrYemek_Menu->balik[4].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 6:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->balik[5].fiyati, ptrYemek_Menu->balik[5].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;

    case 7:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->balik[6].fiyati, ptrYemek_Menu->balik[6].adi, fisIslemSayaci);
        fisIslemSayaci++;
        salata(n);
        break;
    default:
        gecersizGiris();
        break;
    }
}

void salata(int n)
{
    int i, salataCesitSayisi = 4;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.salata[0].adi, "Gobek Salata");
    Yemek_Menu.salata[0].malzemeAdedi = 100;
    Yemek_Menu.salata[0].fiyati = 8.0;

    strcpy(Yemek_Menu.salata[1].adi, "Coban Salata");
    Yemek_Menu.salata[1].malzemeAdedi = 100;
    Yemek_Menu.salata[1].fiyati = 10.0;

    strcpy(Yemek_Menu.salata[2].adi, "Mevsim Salatasi");
    Yemek_Menu.salata[2].malzemeAdedi = 100;
    Yemek_Menu.salata[2].fiyati = 7.0;

    strcpy(Yemek_Menu.salata[3].adi, "Patates Salatasi");
    Yemek_Menu.salata[3].malzemeAdedi = 100;
    Yemek_Menu.salata[3].fiyati = 8.0;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= salataCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("==================>  [%d].%20s: %5.2f%30s", i, Yemek_Menu.salata[i - 1].adi, Yemek_Menu.salata[i - 1].fiyati, "<==================\n\n");
        Sleep(100);
    }

    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        salataSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void salataSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
hataliTuslama:
    echo("\n");

    int salata_secim = secimFonksiyonu();
    switch (salata_secim)
    {
    case 0:
        echo("Salata tercih etmediniz\n");
        echo("Tatli sayfasina yonlendiriliyorsunuz...");
        Sleep(800);
        tatli(n);
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->salata[0].fiyati, ptrYemek_Menu->salata[0].adi, fisIslemSayaci);
        fisIslemSayaci++; //2
        tatli(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->salata[1].fiyati, ptrYemek_Menu->salata[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        tatli(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->salata[2].fiyati, ptrYemek_Menu->salata[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        tatli(n);
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->salata[3].fiyati, ptrYemek_Menu->salata[3].adi, fisIslemSayaci);
        fisIslemSayaci++;
        tatli(n);
        break;
    default:
        puts("Gecersiz giris yaptiniz. Lutfen tekrar deneyiniz. ");
        goto hataliTuslama;
        break;
    }
}

void tatli(int n)
{
    int i, tatliCesitSayisi = 9;
    struct menuBilgi *ptrYemek_Menu;
    ptrYemek_Menu = &Yemek_Menu;

    strcpy(Yemek_Menu.tatli[0].adi, "Kunefe");
    Yemek_Menu.tatli[0].malzemeAdedi = 100;
    Yemek_Menu.tatli[0].fiyati = 13.0;

    strcpy(Yemek_Menu.tatli[1].adi, "Sutlac");
    Yemek_Menu.tatli[1].malzemeAdedi = 100;
    Yemek_Menu.tatli[1].fiyati = 9.0;

    strcpy(Yemek_Menu.tatli[2].adi, "Kadayif");
    Yemek_Menu.tatli[2].malzemeAdedi = 100;
    Yemek_Menu.tatli[2].fiyati = 12.0;

    strcpy(Yemek_Menu.tatli[3].adi, "Baklava");
    Yemek_Menu.tatli[3].malzemeAdedi = 100;
    Yemek_Menu.tatli[3].fiyati = 30.0;

    strcpy(Yemek_Menu.tatli[4].adi, "Trilece");
    Yemek_Menu.tatli[4].malzemeAdedi = 100;
    Yemek_Menu.tatli[4].fiyati = 10.0;

    strcpy(Yemek_Menu.tatli[5].adi, "Hosmerim");
    Yemek_Menu.tatli[5].malzemeAdedi = 100;
    Yemek_Menu.tatli[5].fiyati = 10.0;

    strcpy(Yemek_Menu.tatli[6].adi, "Supangle");
    Yemek_Menu.tatli[6].malzemeAdedi = 100;
    Yemek_Menu.tatli[6].fiyati = 8.0;

    strcpy(Yemek_Menu.tatli[7].adi, "Profiterol");
    Yemek_Menu.tatli[7].malzemeAdedi = 100;
    Yemek_Menu.tatli[7].fiyati = 8.0;

    strcpy(Yemek_Menu.tatli[8].adi, "Cheesecake");
    Yemek_Menu.tatli[8].malzemeAdedi = 100;
    Yemek_Menu.tatli[8].fiyati = 12.0;

    menuRenk();
    cerceve();
    satir_bas(3);

    for (i = 1; i <= tatliCesitSayisi; i++)
    {
        bosluk_bas(3);
        tab_bas(6);

        printf("=====================>    [%d].%10s:%5.2f%25s", i, Yemek_Menu.tatli[i - 1].adi, Yemek_Menu.tatli[i - 1].fiyati, "<=====================\n\n");
        Sleep(100);
    }
    cerceve();

    if (n)
    {
        echo("\n\nadmin yemek guncelleme fonksiyonu");
        //admin yemek guncelleme fonksiyonu
    }
    else
    {
        tatliSecimVeFiyatlandirma(ptrYemek_Menu, n);
    }
}

void tatliSecimVeFiyatlandirma(struct menuBilgi *ptrYemek_Menu, int n)
{
hataliTuslama:
    echo("\n\n");

    int tatli_secim = secimFonksiyonu();
    switch (tatli_secim)
    {
    case 0:
        echo("Tatli tercih etmediniz\n");
        echo("Icecek sayfasina yonlendiriliyorsunuz...");
        Sleep(800);
        icecekler(n);
        break;

    case 1:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[0].fiyati, ptrYemek_Menu->tatli[0].adi, fisIslemSayaci);
        fisIslemSayaci++; //3
        icecekler(n);
        break;

    case 2:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[1].fiyati, ptrYemek_Menu->tatli[1].adi, fisIslemSayaci);
        fisIslemSayaci++;
        icecekler(n);
        break;

    case 3:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[2].fiyati, ptrYemek_Menu->tatli[2].adi, fisIslemSayaci);
        fisIslemSayaci++;
        icecekler(n);
        break;

    case 4:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[3].fiyati, ptrYemek_Menu->tatli[3].adi, fisIslemSayaci);
        fisIslemSayaci++;
        icecekler(n);
        break;

    case 5:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[4].fiyati, ptrYemek_Menu->tatli[4].adi, fisIslemSayaci);
        fisIslemSayaci++;
        icecekler(n);
        break;

    case 6:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[5].fiyati, ptrYemek_Menu->tatli[5].adi, fisIslemSayaci);
        fisIslemSayaci++;
        icecekler(n);
        break;

    case 7:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[6].fiyati, ptrYemek_Menu->tatli[6].adi, fisIslemSayaci);
        fisIslemSayaci++;
        icecekler(n);
        break;

    case 8:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[7].fiyati, ptrYemek_Menu->tatli[7].adi, fisIslemSayaci);
        fisIslemSayaci++;
        icecekler(n);
        break;

    case 9:
        siparisDetaylari(&toplamTutar, ptrYemek_Menu->tatli[8].fiyati, ptrYemek_Menu->tatli[8].adi, fisIslemSayaci);
        fisIslemSayaci++;
        icecekler(n);
        break;

    default:
        cls();
        puts("Gecersiz giris yaptiniz. Lutfen tekrar deneyiniz. ");
        goto hataliTuslama;
        break;
    }
}

void siparisDetaylari(float *fiyatToplam, float tekFiyat, char isim[], int fisIslemSayaci)
{

    printf("\t\t\t\t\t\t%s sectiniz. \n", isim);
    float istenenSayi = 0;
    float toplamFiyat = 0;
    echo("\t\t\t\t\t\tKac tane/porsiyon istersiniz?\n");
    echo("\t\t\t\t\t\t==> ");
    scanf("%f", &istenenSayi);
    *fiyatToplam += istenenSayi * tekFiyat;

    if (fisIslemSayaci == 0) // TODO: 0 bilgisi yani ilk siparis verilince yeni dosya acilacak fis tasarımı baslayacak //cerceve vs
    {
        echo("\n\nFis yazdirma aktif\n"); //? printf programin calisirligini gostermektedir. Programa yazilacak kodlar hazirlaninca silinebilir.
    }
    if (fisIslemSayaci <= 3)
    {
        //TODO: Dosyaya yazilacak bilgiler kismi
        printf("\n\n\t\t\t\t\t\t %s : \t\t %.2f * %.2f \n", isim, tekFiyat, istenenSayi);
        Sleep(1000);
        printf("Aldiklariniz %.2f TL tutmustur.\n", *fiyatToplam);
        echo("\nSiparisiniz hazirlaniyor. Diger sayfaya yonlendiriliyorsunuz...\n");
        Sleep(800);
    }
    if (fisIslemSayaci == 3) //TODO: 3 bilgisi yani son siparis verildigi ve mevcut dosyanin kapatilmasi ve fis bitme tasarımı //cerceve vs
    {
        echo("\nFis sonlandirma aktif\n"); //? printf programin calisirligini gostermektedir. Programa yazilacak kodlar hazirlaninca silinebilir.
    }
    Sleep(2000);
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
    printf("\n\t\t\t\t\t\t");
    int i;
    for (i = 0; i < 80; i++)
    {
        putchar('=');
    }
}

void karsilama()
{
    system("color 2E");
    int i;
    char hosgeldin[50] = "MARMARA KEBAP SALONUNA HOS GELDINIZ";
    satir_bas(16);
    tab_bas(6);

    for (i = 0; i < strlen(hosgeldin); i++)
    {
        system("color 2E");

        printf(" %c", hosgeldin[i]);
        Sleep(25);
    }

    system("color 2E");
    printf("\n\n\t\t\t\t ");

    Sleep(250);
}

void ilerleme(void)
{
    int i;
    for (i = 15; i <= 100; i += 20)
    {
        cls();
        system("color 3E");
        satir_bas(15);
        tab_bas(9);
        bosluk_bas(4);

        printf("%d Yukleniyor... %%", i);

        satir_bas(2);
        tab_bas(7);
        bosluk_bas(4);

        printf("");
        int j;
        for (j = 0; j < i; j += 2)
        {
            printf("\xdb");
            system("color 3E");
        }
        Sleep(10);

        if (i == 90 || i == 50 || i == 96 || i == 35)
        {
            Sleep(25);
        }
    }
}

void musteriEkleme(musterilerPtr *ptr)
{
    system("color 3E");
    printf("\n\t\t");
    system("color 3E");
    bosluk_bas(1);
    tab_bas(4);
    cls();

    int i = 0;

    FILE *musteriKayitlari = fopen("musteriKayitlari.txt", "a"); //dosya acildi.

    // Bu structlar pointer ile musteriGiris fon
    struct musteriBilgileri musteriEkleme[musteriSayisi];
    struct krediKartiBilgileri kredikart[musteriSayisi];
    struct musteriAdresi adres[musteriSayisi];

    if (musteriKayitlari == NULL)
    {
        fprintf(stderr, "Dosyalama isleminde bir sorun olustu...");
    }

    echo("\t\t==> [0].Ana Menu\n");
    echo("\t\t==>Kayit olmak icin herhangi bir sayiya basmaniz yeterlidir:\n");

    int musteriEklemeSecim = secimFonksiyonu();

    if (musteriEklemeSecim == 0)
    {
        ana_menu();
    }

    //!asagidaki degiskenler alinan bilgilerin gecici olarak tutulmasi icin olusturuldu..
    char musteriIsmi[30];
    char musteriSoyismi[30];
    char musteriSifre[15];
    char kartNumarasi[16];
    char kartSahibiAdi[50]; //bitisikYazilmali...
    char gecerlilikTarihi[40];
    char guvenlikKodu[10];
    char sehir[25];
    char ilce[25];
    char semt[25];
    char sokak[25];
    char daireNo[25];

    do //2 ornek olsun diye.
    {

        echo("\n\t\t--Uyelik olusturmak icin lutfen bilgilerinizi giriniz.--\n");
        echo("\n- Adiniz:");
        scanf("%s", &musteriIsmi);
        echo("- Soyadiniz:");
        scanf("%s", &musteriSoyismi);
        echo("- Hesabiniz icin sifre olusturunuz:");
        scanf("%s", &musteriSifre);
        echo("- Kredi karti numaraniz:");
        scanf("%s", &kartNumarasi);
        echo("- Kredi karti sahibi adi ve soyadi (bitisik yazilmalidir!!): ");
        scanf("%s", &kartSahibiAdi);
        echo("- Kredi karti son gecerlilik tarihi (ay ve yil bitisik yazilmalidir!!): ");
        scanf("%s", &gecerlilikTarihi);
        echo("- Kredi karti guvenlik numaraniz: ");
        scanf("%s", &guvenlikKodu);
        echo("- Evinizin bulundugu sehir:");
        scanf("%s", &sehir);
        echo("- Ilce: ");
        scanf("%s", &ilce);
        echo("- Mahalle: ");
        scanf("%s", &semt);
        echo("- Sokak: ");
        scanf("%s", &sokak);
        echo("- Ev NO: ");
        scanf("%s", &daireNo);

        //!Burada girilen bilgilerin uzunlugu kadar bellekte alan acildi..
        musteriEkleme[i].musteriIsmi = (char *)malloc(sizeof(char) * strlen(musteriIsmi));
        musteriEkleme[i].musteriSoyismi = (char *)malloc(sizeof(char) * strlen(musteriSoyismi));
        musteriEkleme[i].musteriSifre = (char *)malloc(sizeof(char) * strlen(musteriSifre));
        kredikart[i].kartNumarasi = (char *)malloc(sizeof(char) * strlen(kartNumarasi));
        kredikart[i].kartSahibiAdi = (char *)malloc(sizeof(char) * strlen(kartSahibiAdi));
        kredikart[i].gecerlilikTarihi = (char *)malloc(sizeof(char) * strlen(gecerlilikTarihi));
        kredikart[i].guvenlikKodu = (char *)malloc(sizeof(char) * strlen(guvenlikKodu));
        adres[i].sehir = (char *)malloc(sizeof(char) * strlen(sehir));
        adres[i].ilce = (char *)malloc(sizeof(char) * strlen(ilce));
        adres[i].semt = (char *)malloc(sizeof(char) * strlen(semt));
        adres[i].sokak = (char *)malloc(sizeof(char) * strlen(sokak));
        adres[i].daireNo = (char *)malloc(sizeof(char) * strlen(daireNo));

        //!burada alinan bilgiler structlara kopyalandi...
        strcpy(musteriEkleme[i].musteriIsmi, musteriIsmi);
        strcpy(musteriEkleme[i].musteriSoyismi, musteriSoyismi);
        strcpy(musteriEkleme[i].musteriSifre, musteriSifre);
        strcpy(kredikart[i].kartNumarasi, kartNumarasi);
        strcpy(kredikart[i].kartSahibiAdi, kartSahibiAdi);
        strcpy(kredikart[i].gecerlilikTarihi, gecerlilikTarihi);
        strcpy(kredikart[i].guvenlikKodu, guvenlikKodu);
        strcpy(adres[i].sehir, sehir);
        strcpy(adres[i].ilce, ilce);
        strcpy(adres[i].semt, semt);
        strcpy(adres[i].sokak, sokak);
        strcpy(adres[i].daireNo, daireNo);

        //!Dosyaya yazdirma islemleri yapildi.
        fprintf(musteriKayitlari, "-Ad: %s\t-Soyad: %s\t-Sifre: %s\n", musteriEkleme[i].musteriIsmi, musteriEkleme[i].musteriSoyismi,
                musteriEkleme[i].musteriSifre);
        fprintf(musteriKayitlari, "-Kart Numarasi: %s\t-Kart Uzerindeki Isim: %s\n", kredikart[i].kartNumarasi, kredikart[i].kartSahibiAdi);
        fprintf(musteriKayitlari, "-Gecerlilik Tarihi: %s\t-Guvenlik Kodu: %s\n", kredikart[i].gecerlilikTarihi, kredikart[i].guvenlikKodu);
        fprintf(musteriKayitlari, "-Sehir: %s\t%-Ilce: %s\t-Mahalle: %s\n", adres[i].sehir, adres[i].ilce, adres[i].semt);
        fprintf(musteriKayitlari, "-Sokak: %s\t-Ev No: %s\n", adres[i].sokak, adres[i].daireNo);

        fprintf(musteriKayitlari, "============================================================================\n");
    } while (i == -1);
    i++;
    echo("Basariyla yeni musteri kaydi olusturulmustur...\n\n");
    Sleep(250);
    fclose(musteriKayitlari);
    echo("Anasayfaya yonlendiriliyorsunuz...\n\n");
    Sleep(1000);
    ana_menu();
}

void musteriKayitlariniGoruntule()
{
    system("color 3E");
    printf("\n\t\t");
    system("color 2E");
    bosluk_bas(1);
    tab_bas(5);
    cls();

    int i;

    FILE *musteriEkranaYazdirma = fopen("musteriKayitlari.txt", "r");

    char *karakter, satir[200]; //! dosyadan okunan karakterler satirda tutuldu sonra karakter ile ekrana yazdirildi...

    printf("\t\t==> [0].Ana Menu\n");
    printf("\t\t==>[1].Kullanici Bilgileri Goruntule\n");

    int musteriEklemeSecim = secimFonksiyonu();
    if (musteriEklemeSecim == 0)
    {
        ana_menu();
    }

    if (musteriEkranaYazdirma == NULL)
    {
        fprintf(stderr, "Dosyalari okurken bir hata meydana geldi...");
    }

    do
    {
        tab_bas(2);
        karakter = fgets(satir, 200, musteriEkranaYazdirma); //!satir satir bilgi okundu...
        if (karakter != NULL)
        {
            printf("%s", satir);
        }
    } while (karakter != NULL);

    printf("\t\t Kayit olan tum kullanicilar goruntulenmektedir..\n");
    printf("\t\t Ana Menuye yonlendiriliyorsunuz..");
    Sleep(10000);
    ana_menu();
}

void uygulamayiKapat()
{
    cls();
    satir_bas(10);
    cerceve();
    satir_bas(2);
    tab_bas(7);
    puts("Yine bekleriz!!\n\n");
    Sleep(200);
    tab_bas(7);
    puts("Program kapatiliyor...\n");
    cerceve();
    Sleep(800);
    exit(1);
}

void gecersizGiris()
{
    cls();
    puts("Gecersiz giris yaptiniz. Lutfen tekrar deneyiniz. ");
    Sleep(1000);
    ana_menu();
}

//Gerekli if yerlerinde kullanılmak uzere secim icin fonksiyon
int secimFonksiyonu()
{
    int secim;
    echo("==> ");
    scanf("%d", &secim);
    return secim;
}

// Console tam ekran yapılıyor
void tamEkran()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
}
