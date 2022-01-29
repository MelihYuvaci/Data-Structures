#include <iostream>
#include <cstdlib>

using namespace std;
class veritabani
{

public:
	int ogr_no;
	string ogr_soyad, ogr_ad, ogr_bolum;
	veritabani* left = NULL;
	veritabani* right = NULL;
	int yukseklik = 1;

	int karsilastir(int a, int b)
	{
		return (a > b) ? a : b;
	}


	int height(veritabani* N)
	{
		if (N == NULL)
			return 0;
		return N->yukseklik;
	}
	veritabani* new_node(string soyisim, string isim, string bolum, int no)// Yeni dugum ilk basta yapraklara eklenir.
	{
		veritabani* node = new veritabani();
		node->ogr_soyad = soyisim;
		node->ogr_ad = isim;
		node->ogr_bolum = bolum;
		node->ogr_no = no;
		node->left = NULL;
		node->right = NULL;
		node->yukseklik = 1;

		return(node);
	}


	veritabani* saga_donus(veritabani* y)// Sorunlu dugumu parametre olarak aldik.
	{
		veritabani* x = y->left;
		veritabani* T2 = x->right;


		x->right = y;// Donus islemi yapilir.
		y->left = T2;

		// Saga donus sonrasi yukseklik guncellemesi  
		y->yukseklik = karsilastir(height(y->left), height(y->right)) + 1;
		x->yukseklik = karsilastir(height(x->left), height(x->right)) + 1;

		// Return new root  
		return x;
	}


	veritabani* sola_donus(veritabani* x)// Sorunlu dugumu parametre olarak aldik.
	{
		veritabani* y = x->right;
		veritabani* T2 = y->left;


		y->left = x;// Donme islemi yapilir.
		x->right = T2;

		// Sola donusten sonra yukseklik guncellemesi
		x->yukseklik = karsilastir(height(x->left), height(x->right)) + 1;
		y->yukseklik = karsilastir(height(y->left), height(y->right)) + 1;

		// Return new root  
		return y;
	}



	int dengeli_mi(veritabani* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}


	veritabani* ekle(veritabani* node, string soyisim, string isim, string bolum, int no)
	{

		if (node == NULL)
			return(new_node(soyisim, isim, bolum, no));

		if (soyisim < node->ogr_soyad)
			node->left = ekle(node->left, soyisim, isim, bolum, no);	// Yapraga inene kadar tekrarlanir.
		else if (soyisim > node->ogr_soyad)
			node->right = ekle(node->right, soyisim, isim, bolum, no);
		else
			return node;


		node->yukseklik = 1 + karsilastir(height(node->left), height(node->right)); // Yukseklik guncelleme.


		int balance = dengeli_mi(node); // Dengeli olup olmadigi kontrol edilir, dengesizse 4 durum vardir.


		// sol sol durumu saga tek donus  
		if (balance > 1 && soyisim < node->left->ogr_soyad)
			return saga_donus(node);

		// sag sag durumu sola tek donus  
		if (balance < -1 && soyisim > node->right->ogr_soyad)
			return sola_donus(node);

		// sol sag durumu cift donus 
		if (balance > 1 && soyisim > node->left->ogr_soyad)
		{
			node->left = sola_donus(node->left);
			return saga_donus(node);
		}

		// sag sol durumu cift donus 
		if (balance < -1 && soyisim < node->right->ogr_soyad)
		{
			node->right = saga_donus(node->right);
			return sola_donus(node);
		}

		
		return node;
	}

	

	string bul(veritabani* root, string soyisim) {

		veritabani* currnode = root;

		while (currnode->ogr_soyad != soyisim)
		{
			if (soyisim > currnode->ogr_soyad)
			{
				if (currnode->right == NULL)
				{
					return "Bulunamadi";
				}
				else
				{
					return veritabani::bul(currnode->right, soyisim);
				}
				
			}
			else
			{
				if (currnode->left == NULL)
				{
					return "Bulunamadi";
				}
				else
				{
					return veritabani::bul(currnode->left, soyisim);
				}
				
			}
			
		}
		return currnode->ogr_soyad;

	}

	void oncekok(veritabani* root)// Oncekok mantigina gore siralanir.
	{
		if (root != NULL)
		{
			cout << root->ogr_soyad << " ";
			oncekok(root->left);
			oncekok(root->right);
		}
	}
	
	
};

class Node {
public:
	int	ogr_no;
	string ogr_ad, ogr_soyad, ogr_bolum;
	Node* next;
};

class list {
public:
	
	Node* head;
	list(void) { head = NULL; }	
	//~list(void);				

													//degisti
	Node* insert_node(int index, int ogr_no, string ogr_isim, string ogr_soyisim, string ogr_bolum) {
		if (index < 0) return NULL;

		int currIndex = 1;
		Node* currNode = head;
		while (currNode && index > currIndex) {
			currNode = currNode->next;
			currIndex++;
		}
		if (index > 0 && currNode == NULL) return NULL;

		Node* newNode = new	Node;
		newNode->ogr_no = ogr_no;
		newNode->ogr_ad = ogr_isim;//degisti
		newNode->ogr_soyad = ogr_soyisim;
		newNode->ogr_bolum = ogr_bolum;
		if (index == 0) {
			newNode->next = head;
			head = newNode;
		}
		else {
			newNode->next = currNode->next;
			currNode->next = newNode;
		}
		return newNode;
	}
	int find_node(int x) {
		Node* currNode = head;
		int currIndex = 1;
		while (currNode && currNode->ogr_no != x) {
			currNode = currNode->next;
			currIndex++;
		}
		if (currNode) return currIndex;
		return 0;
	}
	int delete_node(int x) {
		Node* prevNode = NULL;
		Node* currNode = head;
		int currIndex = 1;
		while (currNode && currNode->ogr_no != x) {
			prevNode = currNode;
			currNode = currNode->next;
			currIndex++;
		}
		if (currNode) {
			if (prevNode) {
				prevNode->next = currNode->next;
				delete currNode;
			}
			else {
				head = currNode->next;
				delete currNode;
			}
			return currIndex;
		}
		return 0;
	}

	void DisplayList()
	{
		
		Node* currNode = head;
		while (currNode != NULL) {
			cout << currNode->ogr_no <<"    ";
			cout << currNode->ogr_ad <<"    ";
			cout << currNode->ogr_soyad <<"    ";
			cout << currNode->ogr_bolum << "     "<<endl;
			currNode = currNode->next;
			
		}
		
	}


};

list iki_dersi_alanlar;

 class veriyapilari : public list {
public:
	

	veriyapilari() {}	// constructor
	~veriyapilari() {}	// destructor
	int Top() {
		if (head == NULL) {
			cout << "Hic ogrenci yok." << endl;
			return -1;
		}
		else
			return head->ogr_no;
	}
	void Push(const int x, string ogr_isim, string ogr_soyisim, string ogr_bolum)  { list::insert_node(0, x, ogr_isim, ogr_soyisim, ogr_bolum); }
	int Pop(int val) {
		if (head == NULL) {
			cout << "Hic ogrenci yok." << endl;
			return -1;
		}
		else {
			 val = head->ogr_no;
			list::delete_node(val);
			return val;
		}
	}

	int toplam_ogr_sayisi() {
		int toplam = 0;
		Node* currnode = head;
		while (currnode != NULL)
		{
			currnode = currnode->next;
			toplam++;
		}
		return toplam;
	}

	void iki_ders_alanlar(veritabani* root) {
		veritabani ogr_bul;
		Node* currnode = head;
		for (int i = 0; i < toplam_ogr_sayisi(); i++)
		{
			string bulunan = ogr_bul.bul(root, currnode->ogr_soyad);

			if (bulunan != "Bulunamadi")
			{
				cout << bulunan << endl;
				iki_dersi_alanlar.insert_node(0, currnode->ogr_no, currnode->ogr_ad, currnode->ogr_soyad, currnode->ogr_bolum);
			}		
			currnode = currnode->next;
		}
	}
	void Aynı_DersAlan_Farklı_Bölümler(veritabani* root) {
		veritabani ogr_bul;
		Node* currnode = head;
		for (int i = 0; i < toplam_ogr_sayisi(); i++)
		{
			string bulunan = ogr_bul.bul(root, currnode->ogr_soyad);

			if (bulunan != "Bulunamadi")
			{
				if(currnode->ogr_bolum!="Bilgisayar")
				cout << bulunan << endl;
			}
			currnode = currnode->next;
		}
	}
	void DisplayStack() { list::DisplayList(); }
	//int veriyapilariders = 0;

	//void swap(veriyapilari* a, veriyapilari* b)
	//{
	//	veriyapilari t = *a;
	//	*a = *b;
	//	*b = t;
	//}
	//int partition(veriyapilari arr[], int low, int high)
	//{
	//	int pivot = arr[high].head->ogr_no;    // pivot
	//	int i = (low - 1);  // Index of smaller element

	//	for (int j = low; j <= high - 1; j++)
	//	{
	//		// If current element is smaller than or
	//		// equal to pivot
	//		if (arr[j].head->ogr_no <= pivot)
	//		{
	//			i++;    // increment index of smaller element
	//			swap(&arr[i], &arr[j]);
	//		}
	//	}
	//	swap(&arr[i + 1], &arr[high]);
	//	return (i + 1);
	//}
	//void hizliSiralama(veriyapilari arr[], int low, int high)
	//{
	//	if (low < high)
	//	{
	//		int pi = partition(arr, low, high);
	//		hizliSiralama(arr, low, pi - 1);
	//		hizliSiralama(arr, pi + 1, high);
	//	}
	//}
	//void hizliSiralama()
	//{


	//	hizliSiralama(, 0, veriyapilariders);
	//	int i;
	//	for (i = 0; i < veriyapilariders; i++)
	//	{
	//		cout << [i];
	//	}
	//}
};

int main()
{
	list veriyapilari_alanlar;
	list liste;
	list AGrubuVeriTabani;
	list BGrubuVeriTabani;
	list AGrubuVeriYapilari;
	list BGrubuVeriYapilari;
	veritabani veritabani_ogr;//AVL
	veriyapilari veriyapilari_ogr;//yigin
	veritabani* root = NULL;	
	int secim;
	int ogr_no;
	string ogr_ad, ogr_soyad, ogr_bolum;
	
	for (int i = 0; true; i++)
	{
		cout << "Ekleme Yapmak Icin-->1" << endl;
		cout << "Eklemeleri yaptiktan sonra diger islemleri yapabilirsiniz!!! " << endl;
		cin >> secim;
		if (secim == 1 || secim == 2)
		{
			system("CLS");
			break;
		}
		else {
			system("CLS");
			continue;
		}
			
	}
	if (secim == 1)
	{
		for (int i = 0; true; i++)
		{
			cout << "Veri yapilari dersi icin eklemek istediginiz ogrencinin bilgilerini giriniz:" << endl;
			cout << "Ogrenci Numarasi: ";
			cin >> ogr_no;
			cout << "Ogrencinin Adi: ";
			cin >> ogr_ad;
			cout << "Ogrencinin Soyadi: ";
			cin >> ogr_soyad;
			cout << "Ogrencinin Bolumu: ";
			cin >> ogr_bolum;

			veriyapilari_ogr.Push(ogr_no, ogr_ad, ogr_soyad, ogr_bolum);

			if (ogr_soyad.at(0) >= 'a' && ogr_soyad.at(0) <= 'k') {
				AGrubuVeriYapilari.insert_node(0, ogr_no, ogr_ad, ogr_soyad, ogr_bolum);
				veriyapilari_alanlar.insert_node(0, ogr_no, ogr_ad, ogr_soyad, ogr_bolum);
			}
			else if (ogr_soyad.at(0) >= 'l' && ogr_soyad.at(0) <= 'z') {
				BGrubuVeriYapilari.insert_node(0, ogr_no, ogr_ad, ogr_soyad, ogr_bolum);
				veriyapilari_alanlar.insert_node(0, ogr_no, ogr_ad, ogr_soyad, ogr_bolum);
			}
			

			int a;
			cout << "Tekrar eklemek ister misiniz? (Evet-->1 Hayir-->0)";
			cin >> a;
				if (a == 1 )
				{
					system("CLS");
					continue;
				}
				else if(a==0) {
					system("CLS");
					break;
				}
				else
				{
					system("CLS");
					break;
				}
		}
		for (int i = 0; true; i++)
		{
			cout << "Veritabani dersi icin eklemek istediginiz ogrencinin bilgilerini giriniz:" << endl;
			cout << "Ogrenci Numarasi: ";
			cin >> ogr_no;
			cout << "Ogrencinin Adi: ";
			cin >> ogr_ad;
			cout << "Ogrencinin Soyadi: ";
			cin >> ogr_soyad;
			cout << "Ogrencinin Bolumu: ";
			cin >> ogr_bolum;

			root = veritabani_ogr.ekle(root, ogr_soyad, ogr_ad, ogr_bolum, ogr_no);			
			if (ogr_no % 2 == 0) {
				AGrubuVeriTabani.insert_node(0, ogr_no, ogr_ad, ogr_soyad, ogr_bolum);
			}
			else
				BGrubuVeriTabani.insert_node(0, ogr_no, ogr_ad, ogr_bolum, ogr_bolum);
			int a;
			cout << "Tekrar eklemek ister misiniz? (Evet-->1 Hayir-->0)";
			cin >> a;
			if (a == 1)
			{
				system("CLS");
				continue;
			}
			else if (a == 0) {
				system("CLS");
				break;
			}
			else
			{
				system("CLS");
				break;
			}
		}
	}
	else if (secim == 2)
	{
		
	}
	int a;
	cout << "Her iki dersi de alan ogrencileri gormek icin--->1" << endl;
	cin >> a;
	if (a==1)
	{
		veriyapilari_ogr.iki_ders_alanlar(root);
	}

	cout << "Sadece veritabani dersini alan ogrencileri goruntulemek icin--->1" << endl;
	cin >> a;

	if (a == 1)
	{
		Node* currnode = iki_dersi_alanlar.head;
		for (int i = 0; i < veriyapilari_ogr.toplam_ogr_sayisi(); i++)
		{
			veriyapilari_alanlar.delete_node(currnode->ogr_no);
			currnode = currnode->next;
			if (currnode==NULL)
			{
				break;
			}
		}
		veriyapilari_alanlar.DisplayList();
	}

	int b;
	cout << "\nHangi dersin grublarini görmek istersiniz? Veritabani(1)-Veriyapilari(2) " << endl;
	cin >> b;
	if (b == 1) {
		cout << "***********************Veri Tabani Gruplari****************************"<<endl;
		cout << "****AGrubu: " << endl;
		AGrubuVeriTabani.DisplayList();
		cout << "****BGrubu: " << endl;
		BGrubuVeriTabani.DisplayList();
	}
	if (b == 2) {
		cout << "**********************Veri Yapilari Ve Algoritmalar *********************" << endl;
		cout << "******AGrubu: " << endl;
		AGrubuVeriYapilari.DisplayList();
		cout << "******BGrubu: " << endl;
		BGrubuVeriYapilari.DisplayList();
	}

	int d;
	cout << "Her iki dersi de alıp farklı bolum ogrencileri gormek icin--->1" << endl;
	cin >> d;
	if (d == 1)
	{
		veriyapilari_ogr.Aynı_DersAlan_Farklı_Bölümler(root);
	}
	int VeriyapilariYapilacakSecimi;
	for (int i = 0; true; i++) {


		
		cout << "Veriyapilarindan silme yapmak icin ---->1" << endl;
		cout << "Veriyapilarında istediginiz ogrenciyi bulmak icin--->2 " << endl;
		cout << "Veriyapilarina en son eklenen elamani bulmak icin---3" << endl;
		cout << "Veriyapilarinda toplam ogrenci sayisini bulmak icin--->4" << endl;
		if (VeriyapilariYapilacakSecimi == 1)
		{
			int SilinecekNo;
			cout << "Silmek istediginiz ogrenci no'yu giriniz->> " << endl;
			cin >> SilinecekNo;
			veriyapilari_ogr.Pop(SilinecekNo);
			Node* currnode = iki_dersi_alanlar.head;
			for (int i = 0; i < veriyapilari_ogr.toplam_ogr_sayisi(); i++)
			{
				veriyapilari_alanlar.delete_node(currnode->ogr_no);
				currnode = currnode->next;
				if (currnode == NULL)
				{
					break;
				}
			}
			veriyapilari_alanlar.DisplayList();

		}
		int TekrarSilsinMi;
		cout << "Tekrar silmek ister misiniz? (Evet-->1 Hayir-->0)";
		cin >> TekrarSilsinMi;
		if (TekrarSilsinMi == 1)
		{
			system("CLS");
			continue;
		}
		else if (TekrarSilsinMi == 0) {
			system("CLS");
			break;
		}
		else
		{
			system("CLS");
			break;
		}
		if (VeriyapilariYapilacakSecimi == 2) {
			int BulunacakNo;
			cout << "Bulmak istediginiz ogrencinin ogrenci No'sunu giriniz->>" << endl;
			cin >> BulunacakNo;
			veriyapilari_ogr.find_node(BulunacakNo);
			break;
		}
		int TekrarBulsunMu;
		cout << "Tekrar bulmak ister misiniz? (Evet-->1 Hayir-->0)";
		cin >> TekrarBulsunMu;
		if (TekrarBulsunMu == 1)
		{
			system("CLS");
			continue;
		}
		else if (TekrarBulsunMu == 0) {
			system("CLS");
			break;
		}
		else
		{
			system("CLS");
			break;
		}
		if (VeriyapilariYapilacakSecimi == 3) {
			veriyapilari_ogr.Top();
			break;
		}
		if (VeriyapilariYapilacakSecimi == 4) {
			veriyapilari_ogr.toplam_ogr_sayisi();
			break;
		}
		int VeriTabaniYapilacakİslemSecimi;
		for (int i = 0; true ; i++)
		{
			cout << "Veritabanindan Soyisimle Bulma Yapmak İcin--->1";
			cin >> VeriTabaniYapilacakİslemSecimi;
			if (VeriTabaniYapilacakİslemSecimi == 1)
			{
				string GirilenSoyİsim;
				cout << "Soyismi Giriniz";
				cin >> GirilenSoyİsim;
				veritabani_ogr.bul(root,GirilenSoyİsim);

			}
			int VeriTabanındaTekrarBulsunMu;
			cout << "Tekrar bulmak ister misiniz? (Evet-->1 Hayir-->0)";
			cin >> VeriTabanındaTekrarBulsunMu;
			if (VeriTabanındaTekrarBulsunMu == 1)
			{
				system("CLS");
				continue;
			}
			else if (VeriTabanındaTekrarBulsunMu == 0) {
				system("CLS");
				break;
			}
			else
			{
				system("CLS");
				break;
			}
		}

	}
	/*int e;
	cout << "Veriyapilari dersinin hızlı sıralama algoritmasını görmek icin--->1" << endl;
	cin >> e;
	if (e == 1) {
		
	}*/
	

	/*int OgrenciNumaralari[20], i = 0;
	while (veriyapilari_alanlar.head != NULL) {
		OgrenciNumaralari[i] = veriyapilari_alanlar.head->ogr_no;
		i++;*/

	
}
  

