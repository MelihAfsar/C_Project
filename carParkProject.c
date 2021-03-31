#include<stdio.h>   
#include<stdlib.h> 
#include<string.h> 
//170420034 Melih Afsar(Afþar)
void homePage();
int selectionFunction();
void vehicleList();
void plaqueList();

struct vehicleInformation{ //Arac bilgilerinin oldugu struct
	char plaque[10];
	char brand[25];
	char model[25];
	char color[20];
};

struct otopark{  //otopark icin gerekli olan giris saati bilgisi ve araclarin oldugu struct
	struct vehicleInformation vehicle;  
	char time[8];
};

struct otopark vehicleAdd(){  //otoparka araclarin bilgisini eklemek icin kullanilan fonksiyon 
	struct otopark carAdd;
	printf("Eklemek Istediginiz Arac \nPlakasi: ");
	scanf("%s",&carAdd.vehicle.plaque);
	printf("Markasi: ");
	scanf("%s",&carAdd.vehicle.brand);
	printf("Modeli: ");
	scanf("%s",&carAdd.vehicle.model);
	printf("Rengi: ");
	scanf("%s",&carAdd.vehicle.color);
	printf("Giris Saati: ");
	scanf("%s",&carAdd.time);
	return carAdd;
}

int main(){
	char exit[1];
	struct otopark car[1000];	
	while(1){  //programin sonlanmamasi icin surekli donen dongu
	homePage();
	int selection = selectionFunction(); 
	if(selection==1){
		system("CLS"); //Ekrandaki yazilarin okunurlugunu artirmak icin kullandim.
		printf("**** Arac Bilgisi Giris Ekranindasiniz ****\n");
		int k;
		for(k=0;k<1000;k++){
			printf("-----------------------------------------------------------------------------\n%d.",k+1);
			car[k]=vehicleAdd();   //arac ekleme fonksiyonunu cagiriyor.
			printf("Hala arac eklemek istiyor musunuz?\n EVET(1)\n HAYIR(2)\n");
			int selection1 = selectionFunction();
			if(selection1==2){
				break;
			}	
		}
			printf("Anasayfaya gitmek icin bir harfe ardindan enter tusuna basiniz.\a\n"); //Ekrandaki bilgileri kullanicinin okumasi icin kullaniciyi bekliyor	
			scanf("%s",exit);
			system("CLS");	
	}
	else if(selection==2){
		system("CLS");
		printf("-----------------------------------------------------------------------------\n");	
		printf("***** Otoparktaki Mevcut Arac Bilgi Goruntuleme Sistemindesiniz *****\n");
		int i;
		for(i=0;i<1000;i++){
			printf("-----------------------------------------------------------------------------\n%d.",i+1);
			vehicleList(car[i]);  //Otoparktaki araclarin bilgilerini goruntulemek icin cagrilan fonksiyon
		}
			printf("Anasayfaya gitmek icin bir harfe ardindan enter tusuna basiniz.\a\n"); //Ekrandaki bilgileri kullanicinin okumasi icin kullaniciyi bekliyor
			scanf("%s",exit);	
			system("CLS");
	}
	else{
		system("CLS");
		int j;
		printf("-----------------------------------------------------------------------------\n");
		printf("***** Otoparktaki Arac Plaka Bilgi Sistemindesiniz *****\n");
		printf("-----------------------------------------------------------------------------\n");
		for(j=0;j<1000;j++){
			printf("%d.",j+1);
			plaqueList(car[j]);  // otoparktaki araclarin yalnizca plaka bilgilerini verir.
			}
			printf("--- Anasayfaya gitmek icin bir harfe ardindan enter tusuna basiniz. ---\a\n");
			scanf("%s",exit);
			system("CLS");
		}
	}
    return 0;	
}

void homePage(){  //Anasayfa goruntusu
	printf("-----------------------------------------------------------------------------\n");
	printf(" #### AFSARPARK Bilgi Ekranina Hos Geldiniz. ####\n");
	printf(" [1] Arac Bilgisi Girisi Yap\n [2] Mevcut Arac Bilgileri\n [3] Otoparktaki Arac Plaka Bilgileri\n");
	printf("-----------------------------------------------------------------------------\n");
}

int selectionFunction(){   //Gerekli if yerlerinde kullanilmak uzere secim icin fonksiyon 
	int selection;
	scanf("%d",&selection);
	return selection;
}

void vehicleList(struct otopark car){	//Arac bilgi gosterme fonksiyonu
	printf("Arac\n Plaka: %s\n Marka: %s\n Model: %s\n Renk: %s\n Giris Saati: %s\n\n",
		car.vehicle.plaque,car.vehicle.brand,car.vehicle.model,car.vehicle.color,car.time);	
}
void plaqueList(struct otopark plaque){  //Arac plaka bilgisi gosterme fonksiyonu
	printf("Arac plaka: %s\n",plaque.vehicle.plaque);
}
