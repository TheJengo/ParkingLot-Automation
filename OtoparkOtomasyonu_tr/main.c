#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/* Global Variables*/
int countTry=0; // Hata Sayaci
int park[25][10]; // Otopark icinde bulunan araclar dizisi

int main()
{   /* Local Variables */
    setlocale(LC_ALL, "Turkish");
    int countCar=240,carProperty=4;
    /*
        countCar degiskeninin 240 degerini almasinin sebebi
        bu otoparka bir gun icerisinde park edebilecek
        farkli arac sayisinin 240 olmasindan kaynaklidir.

        carProperty ise kaydi yapilacak aracin 4 sutunda
        [Tipi] [Plakasi] [Giris Saati] [Cikis Saati]
        aracin ilgili degerlerini tutar.
    */
    int car[countCar][carProperty]; //Arac Kayitlarini Tutan dizi
    int payment[countCar][carProperty-2];
    /*
        Kayidi Basariyla tamamlanmis araclarin Ucretlerinin tutuldugu dizi
        [Plaka] [Ucret]
        olarak iki sutundan olusur.
    */
    int lastCarPos=0; // Eklenen son aracin indis degerini tutan degisken
    char forMenu;   // Menu icin harf tutan degisken

    setZero(24,10,park);
    setZero(countCar,carProperty,car);
    setZero(countCar,carProperty-2,payment);
    /*
        Yukaridaki uc fonksiyon dizilerin icindeki
        butun elemanlarin degerlerini "0" sayisina esitler.
        park[24][10] = {0}; ve ya park[24][10] = 0;
        ifadelerinden hicbirinden sonuc alinamadigi icin bu yonteme basvurulmustur.
    */

    /* Menu Process */
    do{
    int menuChoise=0; // Menu de secilen islemi tutacak degisken
    printf("Arac Ekle/Cikar islemleri icin\t\t\t-1 e\nAraclari Listelemek icin\t\t\t-2 ye\nUcret Sorgulamak icin\t\t\t\t-3 e\nMaksimum ve Minimum Ucret Sorgulamak icin\t-4 e Basiniz : ");
    scanf("%d",&menuChoise);
    printf("\n");
    printf("--------------------------------------------------------\n");
    switch(menuChoise)
    {
        /* Arac Ekle/Cikar Islemleri */
        case 1:
                countTry=0;
                do{
                    int processChoise=0; // Secilecek islemi tutacak degisken
                    printf("Eklemek Icin\t\t-1\nCikarmak Icin\t\t-2 Seciniz : "); scanf("%d",&processChoise);
                    printf("\n");
                    if(processChoise == 1)
                    {
                        lastCarPos = addCar(countCar,carProperty,car,payment,lastCarPos);
                        /*
                            addCar fonksiyonunun calisma mantigi fonksiyonun icerisinde bulunmaktadir.
                            Bu satir calistirilan fonksiyonun geri dondurdugu degeri
                            Son indis degeri olarak lastCarPos degiskenine atar ve sonraki kullanimlarda
                            sureklilik saglar
                        */
                        countTry = 3;
                    }
                    else if(processChoise == 2)
                    {
                       countTry=0;
                        do{
                            int carPlate=0; // Girilen Plaka degerini tutacak degisken
                            listCars(lastCarPos,carProperty,car);
                            /*
                                Arac Kayitlarini Listeler
                            */
                            printf("Silinmesini istediginiz aracin Plaka bilgisini giriniz:"); scanf("%d",&carPlate);
                            if(checkInArray(countCar,carProperty,car,carPlate) == 1)
                            {
                                deleteCar(lastCarPos,carProperty,car,payment,carPlate,lastCarPos);
                                /*
                                    Fonksiyonun calisma mantigi fonksiyon icerisinde bulunmaktadir.
                                    Girilen Plaka degerini ve ilgili plakaya ait butun verileri butun dizilerde temizler.
                                */
                                printf("%d plakali arac kayit listesinden cikartildi.\n",carPlate);
                                printf("\n");
                                countTry = 3;
                            }
                            else{
                                printf("Girdiginiz Plaka bilgisine ait kayitli arac bulunmamaktadir.\n");
                                countTry++;
                            }
                            /*
                                checkInArray fonksiyonundan donen deger eger 1 ise yani
                                ilgili plaka degeri Arac Kayit listesinde bulunuyorsa islem yapmaya devam eder.
                                Bulunmuyor ise, else blogundaki Hata bildirilir.
                            */
                       }while(countTry != 3);
                    }
                    else
                    {
                      countTry++;
                      tryChecker(countTry);
                      /*
                        ilgili fonksiyon genel hata sayma islemlerini uygulular ve ilgili ciktilari kullaniciya ulastirir.
                      */
                    }
                }while(countTry!=3);
                returnMenu(forMenu);
                /*
                    Hata sayma islemlerinden sonra kullaniciya Menu ye don/donme sorgusu yapar.
                */
        break;

        /* Listeleme Islemleri */
        case 2:
            countTry=0;
                do{
                    int processChoise=0;
                    printf("Kayitli Araclar icin\t\t\t-1 e\nOtopark Arac Bilgisi icin\t\t-2 ye basiniz : "); scanf("%d",&processChoise);
                    printf("\n");
                    if(processChoise == 1)
                    {
                        if(lastCarPos == 0)
                        {
                            printf("Arac Kaydi bulunmamaktadir. Lutfen Arac Kaydi olusturunuz...\n");
                            countTry = 3;
                        }
                        listCars(lastCarPos,carProperty,car);
                        countTry = 3;
                    }
                    else if(processChoise == 2)
                    {
                        countTry=0;
                        int inHour,exitHour; // Giris/Cikis Saatlerini tutacak Degiskenler
                        do{
                            printf("Giris Saati <0-24> : ");
                            scanf("%d",&inHour);
                            printf("Cikis Saati <1-24> : ");
                            scanf("%d",&exitHour);
                            /* Giris/Cikis Saatlerinin Kontrolleri */
                            if(inHour>24 || inHour<-1 || exitHour<0 || exitHour>24 )
                            {
                                countTry++;
                                inHour=0;
                                exitHour=0;
                                printf("Gecersiz giris/cikis saati!\n");
                            }
                            else if(exitHour<=inHour)
                            {
                            countTry++;
                            inHour=0;
                            exitHour=0;
                            printf("Cikis saati giris saatinden once olamaz!\n");
                            }
                            else{
                            listPark(inHour,exitHour);
                            /*
                                Otoparkta bulunan araclarin listesi
                            */
                            countTry = 3;
                            }
                        }while(countTry!=3);
                    }
                    else
                    {
                      countTry++;
                      tryChecker(countTry);
                    }
                }while(countTry!=3);
              returnMenu(forMenu);
        break;

        /* Ucret Bilgilerine dair Islemler */
        case 3:
           countTry=0;
                do{
                    int carPlate=0,carPosition=0;
                    if(lastCarPos == 0)
                    {
                        printf("Arac Kaydi bulunmamaktadir. Lutfen Arac Kaydi olusturunuz...\n");
                        countTry = 3;
                    }
                    else{
                        listCars(lastCarPos,carProperty,car);
                        printf("Ucret Bilgisini ogrenmek istediginiz aracin plakasini giriniz : "); scanf("%d",&carPlate);
                        if(checkInArray(countCar,carProperty,car,carPlate) == 1)
                        {
                            carPosition = paymentDetails(countCar,carProperty,car,carPlate);
                            /*
                                Plakasi girilen aracin Arac Kayitlarindaki indisine ulastigimiz Fonksiyon
                                Bu fonksiyonun yazilma sebebi ilgili araca dair bilgilere ulasmak ve bunlari
                                Main fonksiyonu icerisinde kullanmak icindir.
                            */
                            printf("\nPlaka :\t\t%d\nGiris Saati :\t%d\nCikis Saati :\t%d\nArac Tipi:\t%d\nUcret :\t\t%d TL\n\n",car[carPosition][1],car[carPosition][2],car[carPosition][3],car[carPosition][0],payment[carPosition][1]);
                            countTry = 3;
                        }
                        else{
                            printf("Girdiginiz Plaka bilgisine ait kayitli arac bulunmamaktadir.\n");
                            countTry++;
                        }
                    }
                }while(countTry!=3);
             returnMenu(forMenu);
        break;

        /* Maksimum/Minimum Ucret Bilgileri */
        case 4:
            countTry=0;
            do{
                int processChoise=0,max = 0,min = 0; // Maximum ve Minimum degerleri tutacak degiskenler
                printf("En yuksek odeme icin\t\t-1 e\nEn dusuk odeme icin\t\t-2 ye Basiniz : "); scanf("%d",&processChoise);
                if(processChoise == 1)
                    {
                        max = payMax(lastCarPos,carProperty,payment,lastCarPos);
                        /*
                            ilgili fonksiyon ile Ucretler dizisi icerisindeki En buyuk
                            odenen miktari max degiskenine atýyoruz.
                        */
                        if(max == 0) // Eger Max = 0 ise Dizi bostur, Cunku dizilerimde bos olan yer silinmez dizi boyutunda her hangi bir degisiklik yapilmaz
                        {
                            printf("Arac Kaydi bulunmamaktadir. Lutfen Arac Kaydi olusturunuz...\n");
                        }
                        else{
                            printf("Kayitli En Yuksek Ucret %d TL'dir.\n",max);
                        }
                        countTry = 3;
                    }
                    else if(processChoise == 2)
                    {
                        min = payMin(lastCarPos,carProperty,payment,lastCarPos);
                        /*
                            ilgili fonksiyon ile Ucretler dizisi icerisindeki En kucuk
                            odenen miktari min degiskenine atýyoruz.
                        */
                        if(min == 0) // Eger Min = 0 ise Dizi bostur, Cunku dizilerimde bos olan yer silinmez dizi boyutunda her hangi bir degisiklik yapilmaz
                        {
                            printf("Arac Kaydi bulunmamaktadir. Lutfen Arac Kaydi olusturunuz...\n");
                        }
                        else{
                            printf("Kayitli En Dusuk Ucret %d TL'dir.\n",min);
                        }
                        countTry = 3;
                    }
                    else{

                    }
            }while(countTry != 3);
           returnMenu(forMenu);
        break;

        default:
            countTry++;
            tryChecker(countTry);
        break;
    }
    }
    while(countTry!=3);
}
/* FUNCTIONS */

/* Arac Ekle Fonksiyonu */
int addCar(int countCar,int carProperty,int car[countCar][carProperty],int payment[countCar][carProperty-2],int lastCarPos){
    /*
        Gerekli parametreler sirasiyla satir,sutun ,Arac dizisi, Ucret dizisi ve eklenen Son aracin Indisi
    */
    int i,j;
    int flagOne=0,flagTwo=0,flagThree; // Bayraklar Tanimlaniyor
    for(i=lastCarPos;i<lastCarPos+1;i++)
    {
        /* Gerekli Arac Bilgilerinin Alinmasi */
        for(j=0;j<carProperty-1;j++)
        {
            countTry=0;
            if(j==0)
            {   do{
                printf("Motorsiklet\t\t>1\nKisisel Arac\t\t>2\nTicari Arac\t\t>3\nAracinizin Tipi:");
                scanf("%d",&car[i][j]);
                if(car[i][j]>3 || car[i][j]<1){
                    countTry++;
                    car[i][j]=0;
                    /*
                        Eger Arac Tipi yanlis girilirse deger 0 olarak atanir
                        boylece dizime yanlis bir deger ile doldurmus olmam.
                        Cunku direkt Dizimin icine ataniyor klavyeden girilen deger.
                    */
                    printf("Gecersiz Arac Tipi lutfen 1-3 arasinda bir deger giriniz.\n");
                }
                else{
                    countTry = 3;
                }
                }while(countTry!=3);
            }
            else if(j==1)
            {   do{
                if(car[i][0]==1){
                    printf("Aracinizin Plakasi (---) : ");
                }
                else if(car[i][0]==2){
                    printf("Aracinizin Plakasi (----) : ");
                }
                else{
                    printf("Aracinizin Plakasi (-----) : ");
                }
                scanf("%d",&car[i][j]);
                    if((car[i][j]>1000 || car[i][j]<100) && car[i][0]==1)
                    {
                        countTry++;
                        car[i][j]=0;
                        printf("Gecersiz Plaka Lutfen 3 basamakli plakanizi giriniz.\n");
                    }
                    else if((car[i][j]>10000 || car[i][j]<1000) && car[i][0]==2)
                    {
                        countTry++;
                        car[i][j]=0;
                        printf("Gecersiz Plaka Lutfen 4 basamakli plakanizi giriniz.\n");
                    }
                    else if((car[i][j]>100000 || car[i][j]<10000) && car[i][0]==3)
                    {
                        countTry++;
                        car[i][j]=0;
                        printf("Gecersiz Plaka Lutfen 5 basamakli plakanizi giriniz.\n");
                    }
                    /*
                        Yukaridaki 3 sorguda oldugu gibi yine car[i][j] yani plaka degerim
                        yanlis girildigi takdirde 0 degerine geri donduruluyor.
                    */
                    else{
                        countTry=3;
                    }
                }while(countTry!=3);
            }
            else{
                do{
                    printf("Giris Saati <0-24> : ");
                    scanf("%d",&car[i][j]);
                    printf("Cikis Saati <1-24> : ");
                    scanf("%d",&car[i][j+1]);
                    if(car[i][j]>24 || car[i][j]<-1 || car[i][j+1]<0 || car[i][j+1]>24 )
                    {
                        if(car[i][j]==0)
                        {
                            flagThree=1;
                        }
                        else{
                             car[i][j]=0;
                        }
                        countTry++;
                        car[i][j+1]=0;
                        printf("Gecersiz giris/cikis saati!\n");
                    }
                    else if(car[i][j+1]<=car[i][j])
                    {
                        countTry++;
                        car[i][j]=0;
                        car[i][j+1]=0;
                        printf("Cikis saati giris saatinden erken olamaz!\n");
                    }
                    /*
                        Yukaridaki 2  sorguda oldugu gibi yine car[i][j] ve car[i][j+1]
                        giris ve cikis saati degerlerim
                        yanlis girildigi takdirde 0 degerine geri donduruluyor.
                    */
                    else
                    {
                        countTry=3;
                    }
                }while(countTry !=3);
            }
        }
        /*
            Yukaridaki deger atama kontrollerinin tamamlanmasi
            Diziye Aracin eklendigi Anlamina gelmiyor
        */
        /*
            Eger Yeni eklenen degerler Arac Kayit dizisi icerisinde zaten var ise
            yani 1 den fazlaysa islem asagidaki sorguyla basarisizlikla sonuclaniyor
        */
        if(checkInArray(countCar,carProperty,car,car[i][1]) != 1)
        {
            if(checkInArray(countCar,carProperty,car,car[i][1]) == 0)
            {
                printf("Arac Ekleme Basarisiz!(Gecersiz Veri Girisi)\n");
            }
            flagOne=1;
            printf("Arac Ekleme Basarisiz!(Ayni Arac iki kez eklenemez.)\n");
        }
        /*
            Ve Eger Yukaridaki sorgular sonucunda arac bilgisinde eksik bir deger
            yani 0 degeri var ise asagidaki islem ile kontrol ediliyor
        */
        for(j=0;j<carProperty;j++)
        {   if((flagThree == 1 && j!=2) || flagThree == 0)
            {
                if(car[i][j]==0)
                {
                    flagTwo=1;
                    printf("Arac Ekleme Basarisiz!(Gecersiz Veri Girisi)\n");
                    printf("%d\n",j);
                }
            }
        }
        /*
            Yukaridaki 2 sorgu icerisinde bulunan Flaglarin(Bayraklarin) kullanilma nedeni program akisi sirasinda
            programin bu sorgularin icine girip girmedigini anlamak uzere olusturulmustur.
        */
        /*
            Eger yukarida bulunun iki sorguya girilmiyorsa
            Otoparka ekleme islemlerine baslanir
        */
        if(flagOne == 0 && flagTwo == 0 )
        {
            /*
                addToPark sorgusu 0 donduruyorsa
                Bu demektir ki otoparka eklenmek uzere olan aracin giris/cikis saatleri icersinde
                Otoparkta yeterli kapasite bulunmadigini belirtir
                addToPark Fonksiyonu Otoparkta yer var ise 1 yok ise 0 degerini dondurur.
            */
            if(addToPark(car[i][2],car[i][3],car[i][1]) == 0)
            {
                printf("Otoparkta belirttiginiz saattler icerisinde yeterli bos yer bulunmamaktadir.\nBos saatlerimizi ogrenmek icin Ana Menu'den Otopark Arac/Saat listesinden ulasabilirsiniz.\n");
                /*
                    Ekleme basarisiz. Eklenen degerleri 0'la ve son indisi geri dondur.
                */
                for(j=0;j<carProperty;j++)
                {
                    car[i][j]=0;
                }
                return lastCarPos;
            }
            /*
                Eger her Hangi bir Basarisizlik ile karsilasilmadiysa
                Kayit bilgilerini kullanarak Ucret dizisine ekle
            */
            else{
            printf("Arac Ekleme Basarili!\n");
            payment[i][0] = car[i][1];
            payment[i][1] = calculatePayment(car[i][0],car[i][3]-car[i][2]);
            }
        }
        else{
            /*
                Ekleme basarisiz. Eklenen degerleri 0'la ve son indisi geri dondur.
            */
            for(j=0;j<carProperty;j++)
            {
                 car[i][j]=0;
            }
            return lastCarPos;
        }
    }
    lastCarPos = i;
    return lastCarPos;
}
/* Otoparka Ekle Fonksiyonu */
int addToPark(int inHour,int exitHour,int carPlate){
    /*
        Parametreler sirasiyla giris saati, cikis saati, plaka.
        Her saat icin arac plakasini otopark icerisinde bos olan ilk yere
        Arac plakasini ekler.
    */
    int i,j,indexPlate,capacity=0;
    /*
        Plakalarin indexini tutan indexPLate
        ve
        Saat icerisindeki kapasiteyi tutan capacity
        degiskenleri tanimlaniyor
    */
    for(i=inHour;i<exitHour;i++)
    {
        indexPlate=0;
        capacity=0;
        for(j=0;j<10;j++)
        {
            if(park[i][j]==0)
            {
                park[i][indexPlate]=carPlate;
                indexPlate++;
                break;
            }
            else
            {
                capacity++;
                indexPlate++;
                if(park[i][j]==carPlate)
                    continue;
                if(capacity == 10 )
                    return 0;
            }
        }
    }
    return 1;
}

/* Arac Kayit Silme Fonksiyonu */
void deleteCar(int countCar,int carProperty,int car[countCar][carProperty],int payment[countCar][carProperty-2],int plate,int lastCarPos){
        /*
            Parametreler sirasi ile, satir,sutun,Arac Kayitlari dizisi, Ucret Kayitlari dizisi, plaka, Eklenen en son aracin indisi
            1. adimda Gelen parametreler ile Plaka bilgisinin bulundugu indisteki butun degerleri Arac Kayit dizisinde 0'lar yani siler.
            2. adimda Plaka bilgisine ait Ucret Kayitlarini temizler.
            3. adimda Park bilgisinde kayitli bulundugu saatlerden plakasini temizler
        */
        int i,j;
        for(i=0;i<lastCarPos;i++)
        {
            if(car[i][1] == plate)
            {
                for(j=0;j<carProperty;j++)
                {
                    car[i][j]=0;
                }
            }
            if(payment[i][0] == plate)
            {
                 for(j=0;j<carProperty-2;j++)
                {
                    payment[i][j]=0;
                }
            }
        }
        for(i=0;i<24;i++)
        {
            for(j=0;j<10;j++)
            {
                if(park[i][j] == plate)
                 {
                     park[i][j] = 0;
                 }
            }
        }
}
/* Arac Kayitlarini Listeleyen Fonksiyon */
void listCars(int row,int column,int arr[row][column])
{
    /*
      Parametreler sirasiyla satir,sutun,dizi.
      Araclar Dizisini Listeleyen Fonksiyon
    */
    int i,j;
    printf("Tip\t\tPlaka\t\tGiris\t\tCikis\n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
            if(arr[i][j]!=0 && j!=2)
            {
                printf("%d\t\t",arr[i][j]);
            }
            else if(arr[i][j-1] != 0 && j==2)
            {
                printf("%d\t\t",arr[i][j]);
            }
            else
            {
                break;
            }
        }
        if(j==column)
        printf("\n");
    }
}
/* Otoparktaki Araclari Listeleyen Fonksiyon */
void listPark(inHour,exitHour)
{
     /*
      Parametreler sirasiyla giris saati, cikis saati.
      Girilen saat degerleri arasinda otoparktaki araclari listeler
    */
    int i,j;
    printf("Arac  : ");
    for(i=1;i<=10;i++)
        printf("%d\t",i);
    printf("\n");
    for(i=inHour;i<exitHour;i++)
    {   if(i<10)
        {
            printf("0%d:00 : ",i);
        }
        else{
            printf("%d:00 : ",i);
        }
        for(j=0;j<10;j++)
        {
            if(park[i][j]==0)
                printf("--\t");
            else
            printf("%d\t",park[i][j]);
        }
        printf("\n");
    }
}
/* Ucret Hesapla Fonksiyonu */
int calculatePayment(int type, int hour){
    /*
        Girilen Parametreleri tip ve saate gore
        Odenecek miktari geri donduren fonksiyon
    */
        int payMuch = 5;
        if(type==1)
            payMuch += hour ;
        else if(type == 2)
            payMuch += (hour * 2);
        else
            payMuch += (hour * 3);
        return payMuch;
}
/* Ucret Detay Fonksiyonu */
int paymentDetails(int countCar,int carProperty,int car[countCar][carProperty],int plate){
    /*
         Girilen parametrelerden plaka bilgisi ile ilgili aracin dizi icerisindeki
         indisini geri donduren fonksiyon
    */
    int i,j;
    for(i=0;i<countCar;i++)
    {
        if(car[i][1] == plate)
        {
            return i;
        }
    }
}
/* Maksimum Ucret Fonksiyonu */
int payMax(int countCar,int carProperty,int payment[countCar][carProperty-2],int lastCarPos){
          int i;
          int payMax=payment[0][1];
          for(i=1;i<lastCarPos;i++)
          {
              if(payMax<payment[i][1] && payment[i][0] != 0)
                payMax = payment[i][1];
          }
          return payMax;
}
/* Minimum Ucret Fonksiyonu */
int payMin(int countCar,int carProperty,int payment[countCar][carProperty-2],int lastCarPos){
          int i,j;
          int payMin=0;
          for(i=0;i<lastCarPos;i++)
          {
              if(payment[i][0]!=0)
              {
                payMin=payment[i][0];
                break;
              }
          }
          for(j=i;j<lastCarPos;j++)
          {
                if(payment[j][0]==0)
                {
                    continue;
                }
                else{if(payMin>payment[j][1])
                {
                    payMin = payment[j][1];
                }
                }

            }
          return payMin;
}
/* Dizi Ici Kontrol Fonksiyonu */
int checkInArray(int row,int column, int arr[row][column],int value){
    /*
        Girilen deger parametresini dizi icerisinde arayan ve
        varsa sayisini geri donduren fonksiyon
    */
    int i,j;
    int isThere=0;
    for(i=0;i<row;i++)
    {
        if(value == arr[i][1])
            isThere++;
    }
    return isThere;
}
/* 0'layan Fonksiyon */
void setZero(int row,int column,int arr[row][column]){
    /*
        Istenilen bir matrisin butun elemanlarinin degerini
        0 degeri yapan fonksiyon
    */
    int i,j;
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            arr[i][j]=0;
        }
    }
}
/* Hata Sayan Fonksiyon */
void tryChecker(int countTry)
{
    /*
        Girilen Hata Miktarinin Sayisina gore cikti verir
    */
    if(countTry == 3)
    printf("Program Sonlandiriliyor...");
    else
    printf("Hatali Giris Yaptiniz Lutfen Tekrar Giris yapiniz.\n\n");
}
/* Menuye Don Fonksiyonu */
void returnMenu(char forMenu){
    /*
        Girilen harf ile menuye donme islemini yapar ve ya sonlandirir.
    */
    printf("\nMenuye donmek icin 'E', Sistemden cikmak icin her-hangi bir harf giriniz : ");
    scanf(" %c",&forMenu);
    if(forMenu == 'E' || forMenu == 'e')
    {
        system("CLS");
        countTry = 0;
    }
}
