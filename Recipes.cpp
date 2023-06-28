#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

class Recipe
{
private:
    string fname;
    string fcategory;
    vector<string> fingredients;
public:

    Recipe(string name = "", string category = "", vector<string> ingredients = {}) : fname{name}, fcategory{category}, fingredients{ingredients}
    {}

    vector<string> get_ingredients(void) const { return fingredients; }
    string get_category(void) const { return fcategory; }
    string get_name(void) const { return fname; }
    void set_ingredients(vector<string> ingredients) { fingredients = ingredients; }
    void set_category(string category) { fcategory = category; }
    void set_name(string name) { fname = name; }

    void add_ingredient(string ingredient)
    {
        fingredients.push_back(ingredient);
    }

};

void addRecipe(vector<Recipe>& v);
void modifyMenu(vector<Recipe>& v);
void ModifyRecipe(vector<Recipe>& v, int p);
void printList(vector<Recipe>& v);
void categoryList(vector<Recipe>& v);
void ingredientsList(vector<Recipe>& v);


int main() {

    vector<Recipe> organiser; 
    ifstream file("vector.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int value;
            string name;
            string category; 
            vector<string> ingredients = { "","","","","","","","","","",""};
            ss >> name >> category; 
            for (size_t i = 0; i < ingredients.size(); i++)
            {
                ss >> ingredients[i];
            }
            Recipe obj;
            obj.set_name(name);
            obj.set_category(category);
            obj.set_ingredients(ingredients);
            organiser.push_back(obj);
        }
        file.close();
        cout << "Vector of objects loaded from vector.txt" << endl;
    }
    else {
        cout << "Failed to open vector.txt" << endl;
    }
    
    

    while (true)
    {
        cout << "Please type a number for your choice" << endl;
        cout << "1: Modify Recipes" << endl;
        cout << "2: Add a recipe" << endl;
        cout << "3: List of recipes" << endl;
        cout << "4: List sorted by a category:" << endl;
        cout << "5: List sorted by an ingredients:" << endl;
        cout << "6: Save all changes" << endl; 
        cout << "7: Exit program" << endl << endl;
        int choice;
        cin >> choice;
        
        switch (choice)
        {
        case 1: modifyMenu(organiser);
            break;
        case 2: addRecipe(organiser);
            break;
        case 3: printList(organiser);
            break;
        case 4: categoryList(organiser);
            break;
        case 5: ingredientsList(organiser);
            break;
        case 6: 
        {
            ofstream file("vector.txt");
            if (file.is_open()) {
                for (auto& obj : organiser)
                {
                    file << obj.get_name() << " " << " " << obj.get_category() << " ";
                    for (auto i : obj.get_ingredients())
                    {
                        file << i << " ";
                    }
                    file << endl;
                }
                file.close();
                cout << "Vector of objects saved to vector.txt" << endl;
            }
            else
            {
                cout << "Failed to open txt file" << endl;
            }
            break;
        }
        case 7:
            return 0;
        default:
            cout << "Type correct number!" << endl << endl;
            break;
            
        }

    }

}
void modifyMenu(vector<Recipe>& v)
{
    while (true)
    {
        int itemp = 0;
        cout << "Type number of recipe to modify (-1 to exit):" << endl;
        for (size_t i = 0; i < v.size(); i++)
        {
            cout << itemp + 1 << v[i].get_name() << endl;
            itemp++;
        }
        int choice = 0;
        cin >> choice;
        if (choice>=-1)
        {
            
            if (choice != -1)
            {
                if (choice <= v.size())
                {
                    ModifyRecipe(v, choice - 1);
                }
                else
                {
                    cout << "Type correct number!" << endl << endl; 
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "Type correct number!" << endl << endl;
        }

    }
}

void ModifyRecipe(vector<Recipe>& v, int p)
{
    while (true)
    {
        cout << "Recipe Name: " << v[p].get_name();
        cout << "Please enter a number of your choice" << endl;
        cout << "1: Edit Name" << endl;
        cout << "2: Add Ingredient" << endl;
        cout << "3: Edit category" << endl;
        cout << "4: Exit" << endl << endl;
        int choice = 0;
        cin >> choice;
        string tempstring;
        switch (choice)
        {
        case 1:
            cout << "Type in new name:" << endl;
            getline(cin, tempstring);
            v[p].set_name(tempstring);
            cout << "New name is: " + v[p].get_name() << endl;
            break;
        case 2:
            cout << "Type in name of an ingredient:" << endl;
            cin.ignore();
            getline(cin, tempstring);
            v[p].add_ingredient(tempstring);
            cout << tempstring + " has successfully been added" << endl;
            break;
        case 3:
            cout << "Current category is " + v[p].get_category() + "." << endl;
            cout << "Type in new category:" << endl;
            cin.ignore();
            getline(cin, tempstring);
            v[p].set_category(tempstring);
            cout << "New category is " + v[p].get_category() << endl;
            break;
        case 4:
            return;
        default:
            cout << "Wrong number!" << endl;
            return;
        
        }
    }
}

void addRecipe(vector<Recipe>& v)
{
    while (true)
    {
        string tempstring;
        Recipe temprecipe;
        cout << "Type in name for new recipe:" << endl;
        cin >> tempstring;
        temprecipe.set_name(tempstring);
        cout << "Type in category for new recipe:" << endl;
        cin >> tempstring;
        temprecipe.set_category(tempstring);
        while (true)
        {
            cout << "Type an ingredient (-1 to exit):" << endl;
            cin >> tempstring;
            if (tempstring == "-1")
            {
                break;
            }
            temprecipe.add_ingredient(tempstring);
        }
        v.push_back(temprecipe); 
        cout << "Recipe has been succesfully added!" << endl << endl;
        break;
    }

    
}

void printList(vector<Recipe>& v)
{
    if (v.size() == 0)
    {
        cout << "You have not added any recipes yet!" << endl << endl;

    }
    else
    {
        int choice = 0;
        int itemp = 0;
        int itemp1 = 0;
        for (size_t i = 0; i < v.size(); i++)
        {
            cout << itemp + 1 <<":" << v[i].get_name() << endl;
            itemp++;
        }
        cout << "Type number of recipe you want to see (-1 to exit):" << endl;
        cin >> choice;
        if (choice > 0 && choice <= v.size())
        {
            cout <<"name: "<< v[choice - 1].get_name() << endl;
            cout << "category: " << v[choice - 1].get_category() << endl;
            cout << "ingredients:" << endl;
            for (size_t i = 0; i < v[choice - 1].get_ingredients().size(); i++)
            {
                cout << v[choice - 1].get_ingredients()[i] << endl;
                itemp1++;
            }

            }
        else if(choice == -1)
        {
            return;
        }
        else { cout << "Wrong number!" << endl; return; }

    }
}

void categoryList(vector<Recipe>& v)
{
    
    while (true)
    {
        string tempstring; 
        cout << "Type category (-1 to exit):" << endl;
        cin >> tempstring;
        if (tempstring == "-1")
        {
            return;
        }

        map<string, string> tempmap;
        for (int i=0; i<v.size(); i++)
        {
            if (v[i].get_category() == tempstring)
            {
                tempmap[v[i].get_name()] = v[i].get_category();
            }
            
        }
        
        for (auto element : tempmap)
        {
            string key = element.first;
            string value = element.second;
           
            cout << value<<": "<<key << endl;
            
        }
        return;
    
    }
}

void ingredientsList(vector<Recipe>& v)
{
    string tempstring; 
    while (true)
    {
        
        cout << "Type ingredient (-1 to exit):" << endl;
        cin >> tempstring;
        if (tempstring == "-1")
        {
            return;
        }
        int itemp = 0;
      
        for (size_t i = 0; i < v.size(); i++)
        {
            vector<string> tempvector = v[i].get_ingredients(); 
            for (size_t k=0; k<tempvector.size(); k++)
            {
                if (tempvector[k] == tempstring)
                {
                    cout << v[i].get_name() << endl;
                    
                }
                itemp++;
            }
            
            
        }
        if (itemp == 0)
        {
            cout << "No recipe with given ingredient found" << endl;
        }

    }
}


