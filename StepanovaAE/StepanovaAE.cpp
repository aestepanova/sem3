#ifndef SHOP
#define SHOP

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace shop{

    /// \brief Базовый абстрактный класс
    class Product{
    protected:
        int prod_id; // идентификатор
        string type; // название
        vector<string> files; // список имён файлов, из которых состоит продукт
        bool flag; // флаг корректности установки
    public:
        Product(): prod_id(0), type("product"), flag(false){}
        Product(int _id, string _type, vector<string> _files, bool f){ // инициализирующий конструктор
            prod_id = _id;
            type = std::move(_type);
            flag = f;
            this->files.clear();
            for(int i = 0; i < _files.size(); i++){
                this->files.push_back(_files[i]);
            }
        }
        Product(const Product& pr){
            prod_id = pr.prod_id;
            type = pr.type;
            flag = pr.flag;
            this->files.clear();
            for(int i = 0; i < pr.files.size(); i++){
                this->files.push_back(pr.files[i]);
            }
        }

        int getProdId() const {return prod_id;}
        string getType() const{return type;}
        bool getFlag() const {return flag;}

        Product& setProdId(int id){
            this->prod_id = id;
            return *this;
        }

        Product& setType(string _type){
            this->type = std::move(_type);
            return *this;
        }

        Product& setFlag(bool f){
            this->flag = f;
            return *this;
        }

        Product& addFile(string& file){
            this->files.push_back(file);
            return *this;
        }


        friend ostream& operator << (ostream& s, Product* pr){
            pr->showState();
            return s;
        }

        //метод возвращающий количество зависимостей продукта
        virtual int depends() {return 0;}

        virtual void showState()=0;

        virtual ~Product() = default;
    };

    /*!1. Приложение. Содержит:
- идентификатор и название;
- список имён файлов, из которых состоит продукт;
- путь к исполняемому файлу;
- флаг корректности установки. */
    class App : public Product{
    private:
        string way;
    public:
        App(): Product(), way("C:/User/apps"){}; // пустой инициализирующий конструктор
        App(int _id, string _type, vector<string> _files, string _way, bool f):
            Product(_id, std::move(_type), std::move(_files), f), way(std::move(_way)) {}// инициализирующий конструктор
        App(const App& a) : Product(a), way(a.way) {} // копирующий конструктор
        virtual void showState() {
            cout << "[id]: " << this->prod_id << endl;
            cout << "[name]: " << this->type << endl;
            cout << "[files]: \n";
            vector<string>::iterator it;
            for(it = this->files.begin(); it < this->files.end(); it++){
                cout<< "\t" << (*it) << endl;
            }
            cout << "[way]: " << this->way << endl;
            cout << "[correct installation]: " << this->flag << endl;
        }
        virtual int depends() {
            cout << "This app has " << this->files.size() << "files\n";
            return this->files.size();
        }
    };


    /*!2. Доп-контент. Содержит:
- идентификатор и название;
- список имён файлов, из которых состоит данный продукт;
- вектор дополнительных продуктов, которые могут быть предварительно установлены
(но не обязательно корректно установлены);
- флаг корректности установки.*/
    class AddContent : public Product{
    protected:
        vector<Product*> adds;
    public:
        AddContent(): Product() {}; // пустой инициализирующий конструктор
        AddContent(int _id, string _type, vector<string> _files, vector<Product*> _adds, bool f):
            Product(_id, std::move(_type), std::move(_files), f){ // инициализирующий конструктор
            this->adds.clear();
            for(int i = 1; i < _adds.size(); i++){
                this->adds.push_back(_adds[i]);
            }
        }
        AddContent(const AddContent& a) : Product(a) { // копирующий конструктор
            this->adds.clear();
            for(int i = 1; i < a.adds.size(); i++){
                this->adds.push_back(a.adds[i]);
            }
        }
        virtual void showState() {
            cout << "[id]: " << this->prod_id << endl;
            cout << "[name]: " << this->type << endl;
            cout << "[files]: \n";
            vector<string>::iterator it;
            for(it = this->files.begin(); it < this->files.end(); it++){
                cout<< "\t" << (*it) << endl;
            }
            cout << "[adds]: \n";
            cout << "--------------------\n";
            vector<Product*>::iterator pr;
            for(pr = this->adds.begin(); pr < this->adds.end(); pr++){
                (*pr)->showState();
            }
            cout << "--------------------\n";

            cout << "[correct installation]: " << this->flag << endl;
        }

        virtual int depends() {
            cout << "This add content has " << this->files.size() << " files and " << this->adds.size() << " adds.\n";
            return (this->files.size() + this->adds.size());
        }

        void setFlagMethod(){
            int f = 1;
            vector<Product*>::iterator pr;
            for(pr = this->adds.begin(); pr < this->adds.end(); pr++){
                if ((*pr)->getFlag() == 0) f = 0;
            }
            setFlag(f);
        }
        void addApp(Product* app){
            this->adds.push_back(static_cast<Product*>(app));
        }
    };

    /*!3. Доп-инструментарий. Содержит:
- идентификатор и название;
- список имён файлов, из которых состоит данный продукт;
- вектор дополнительных продуктов, которые могут быть предварительно установлены
(но не обязательно корректно установлены);
- путь к исполняемому файлу;
- флаг корректности установки.*/

    class Addons : public AddContent{
    private:
        string way;
    public:
        Addons(): AddContent(), way("C:/Users/addons"){}
        Addons(int _id, string _type, vector<string> _files, vector<Product*> _adds, string _way, bool f):
            AddContent(_id, std::move(_type), std::move(_files), std::move(_adds), f), way(std::move(_way)){} // инициализирующий конструктор

        Addons(const Addons& a): AddContent(a), way(a.way){} // копирующий конструктор

        virtual void showState() {
            cout << "[id]: " << this->prod_id << endl;
            cout << "[name]: " << this->type << endl;
            cout << "[files]: \n";
            vector<string>::iterator it;
            for(it = this->files.begin(); it < this->files.end(); it++){
                cout<< "\t" << (*it) << endl;
            }
            cout << "[adds]: \n";
            cout << "--------------------\n";
            vector<Product*>::iterator pr;
            for(pr = this->adds.begin(); pr < this->adds.end(); pr++){
                (*pr)->showState();
            }
            cout << "--------------------\n";
            cout << "[way]: " << this->way << endl;
            cout << "[correct installation]: " << this->flag << endl;
        }
    };


    /*!Любые покупки находятся на аккаунте, который описывается именем пользователя, хэш-суммой
//пароля, идентификатором пользователя, а также продуктами, находящимися на аккаунте,
//хранящимися в виде вектора, память под который выделяется динамически */
    class Account{
    private:
        string name;
        int h_sum;
        int user_id;
        vector<Product*> prod;
    public:
        /*Для аккаунта требуется описать и реализовать необходимые конструкторы, деструктор,
методы добавления и удаления продукта на аккаунт, вывода состояния аккаунта в выходной поток
(с помощью перегруженного оператора <<). Также у аккаунта должен быть реализован метод
простейшей проверки целостности продуктов пользователя (подробности ниже).
         * */
        Account(): name("Creator"), h_sum(0), user_id(0){}
        Account(Account& acc): name(acc.name), h_sum(acc.h_sum), user_id(acc.user_id){
            vector<Product*>::iterator it;
            for(it = acc.prod.begin(); it < acc.prod.end(); it++){
                this->prod.push_back(*it);
            }
        }
        /*!методы добавления и удаления продукта на аккаунт, вывода состояния аккаунта в выходной поток
(с помощью перегруженного оператора <<). Также у аккаунта должен быть реализован метод
простейшей проверки целостности продуктов пользователя.*/
        void addProd(Product* prod){
            this->prod.push_back(static_cast<Product*>(prod));
        }

        void deleteProd(int prod_id){
            vector<Product*>::iterator it;
            for(it = this->prod.begin(); it < this->prod.end(); it++){
                if ((*it)->getProdId() == prod_id){
                    this->prod.erase(it);
                }
            }
        }

        int goodProd(){
            int f = 1;
            vector<Product*>::iterator pr;
            for(pr = this->prod.begin(); pr < this->prod.end(); pr++){
                if ((*pr)->getFlag() == 0) f = 0;
            }
            if(f){
                cout << "everything is good!\n";
            }else{
                cout<< "there are some problems with products\n";
            }
        }
        ~Account() = default; // так как stl вектор сам грамотно осовбодит память из-под себя

    };


}

int main(){
    shop::App A;

    int id = 121;
    string name = "GreatName!", way = "Happy way)";
    string f1 = "file1.xlsx", f2 = "f2.exe", f3 = "f3.zip";
    bool f = true;
    vector<string> fls;
    fls.push_back(f1);
    fls.push_back(f2);
    fls.push_back(f3);

    shop::Product *ptrB = new shop::App(id, name,fls, way, f);
    shop::AddContent C;
    shop::Addons D;

    A.showState();
    cout << endl;
    ptrB->showState();
    cout << endl;
    C.addFile(f1);
    C.showState();
    C.depends();
    cout << endl;
    D.addApp(ptrB);
    D.showState();
    cout << "---------\n";
    D.depends();




    return 0;
}
#endif // SHOP