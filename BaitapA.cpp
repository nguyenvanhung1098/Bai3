#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <sstream>
#include <queue>

using namespace std;

vector<string> Works; // mang luu cac tu tieng anh trong file
vector < vector <int> > danhsachke(10000);

int Kiemtra(int n,int khoa[]){ // tra ve dinh chua duoc duyet
    for(int i=0;i<n;i++){
        if(khoa[i]==0){
            return i;
        }
    }
}

void DemLienthong(int n,vector < vector <int> > danhsachke){
    queue <int> Myqueue;
    int khoa[n]={0};// Neu dinh chua duoc duyet thi khoa bang 0
    int dem=0; // Dem so thanh phan lien thong trong do thi
    int soptu=0; //dem so phan tu da duyet
    while(soptu<n){
        int dinh;
        dinh=Kiemtra(n,khoa);
        Myqueue.push(dinh);
        khoa[dinh]=1;
        soptu++;
        dem++;
        while(!Myqueue.empty()){
            dinh=Myqueue.front();
            Myqueue.pop();
            for(int i=0;i<danhsachke[dinh].size();i++){
                if(khoa[danhsachke[dinh][i]]==0){
                    Myqueue.push(danhsachke[dinh][i]);
                    khoa[danhsachke[dinh][i]]=1;
                    soptu++;
                }
            }
        }

}
    cout << "So thanh phan lien thong:"<<dem<<endl;
}

void Duongdingannhat(int u,int v,int n,vector < vector <int> > danhsachke,vector <string> Works){
    vector < vector <int> > Dulieu(10000); // Thu tu luu: Dinh , Cha, khoang cach ,khoa: =1 da duyet va bang 0 chua duyet
    int khoa[n]={0};
    khoa[u]=1;

    int dem=0; //Luu so phan tu da cho vao vector Dulieu
    queue <int> Myqueue;
    queue <int> Fatherqueue;
    Myqueue.push(u);
    Fatherqueue.push(0);
    int dinh;
    int cha=0;

    while(!Myqueue.empty()){

        dinh=Myqueue.front();
        Myqueue.pop();
        cha=Fatherqueue.front();
        Fatherqueue.pop();

        Dulieu[dem].push_back(dinh);//dinh
        Dulieu[dem].push_back(cha);//cha
        dem++;


        for(int i=0;i<danhsachke[dinh].size();i++){
            if(khoa[danhsachke[dinh][i]]==0){
                Myqueue.push(danhsachke[dinh][i]);
                Fatherqueue.push(dem-1);
                khoa[danhsachke[dinh][i]]=1;
            }
        }

    }


    int vitri=1;
    for(int i=0;i<dem;i++){
        if(Dulieu[i][0]==v){
            vitri=i;
        }
    }

    int Duongdi[100];
    Duongdi[0]=v;
    int bo=Dulieu[vitri][1];
    int i=0;
    while(Duongdi[i]!=u){
        i++;
        Duongdi[i]=Dulieu[bo][0];
        bo=Dulieu[bo][1];
    }
    if(i==1) cout<<"Khong co duong di tu "<<Works[u]<<" den "<<Works[v];
    else{
        for(;i>=0;i--){
            cout<< Works[Duongdi[i]]<<" ";
        }
    }

}

int main()
{
    // Nhap vao tu file cac tu tieng anh
    ifstream infile;
    int n=0;// luu so phan tu tieng anh co do dai 5
    string work;
    infile.open("sgb-works.txt", ios::out);
    if(infile.is_open()){
        while(!infile.eof()){
            infile>> work;
            Works.push_back(work);
            n++;
        }
    }
    infile.close();

    // luu lai danh sach ke cua do thi
    int dem=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            dem=0;
            for(int k=0;k<5;k++)
                if(Works[i][k]==Works[j][k])
                    dem++;
            if(dem==4){

                danhsachke[i].push_back(j);// i ung voi Works[i];
            }

        }
    }


    DemLienthong(n,danhsachke);
    string u,v;
    cout <<"Nhap vao dinh dau u"<<endl;
    cin >> u;
    cout <<"Nhap vao dinh cuoi v"<<endl;
    cin >>v;
    int u1=-1,v1=-1;
    for(int i=0;i<n;i++){
        if(Works[i]==u)
            u1=i;
        if(Works[i]==v)
            v1=i;
    }
    if(u1==-1||v1==-1){
        cout <<"Loi dinh khong ton tai!"<<endl;
        return 0;
    }

    Duongdingannhat(u1,v1,n,danhsachke,Works);

    return 0;
}

