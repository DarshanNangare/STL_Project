#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

int main() {
    // vector<int> price;
    // vector<int> discount;
    // vector<int> quantity;
    // vector<int> revenuePerProduct;
    // vector<int> discountedPrice;
    // int totalRevenue;
    // int n;

    // cout<<"Welcome To E-Commerce Website"<<endl;
    // cout<<"Enter the number of products"<<endl;
    // cin>>n;
    
    // for(int i=0;i<n;i++){
    //     int p;
    //     cout<<"Please Enter the Price of the Product "<<i+1<<" : "<<endl;
    //     cin>>p;
    //     price.push_back(p);
    // }

    // for(int i=0;i<n;i++){
    //     int d;
    //     cout<<"Please Enter the Discount of the Product "<<i+1<<" in % : "<<endl;
    //     cin>>d;
    //     discount.push_back(d);
    // }

    // for(int i=0;i<n;i++){
    //     int q;
    //     cout<<"Please Enter the no of units sold of the Product "<<i+1<<" : "<<endl;
    //     cin>>q;
    //     quantity.push_back(q);
    // }

    // for(int i=0;i<n;i++){
    //     discountedPrice.push_back(price[i] - price[i] * discount[i]/100);
    // }

    // for(int i=0;i<n;i++){
    //     revenuePerProduct.push_back(discountedPrice[i]*quantity[i]);
    // }

    // totalRevenue = accumulate(revenuePerProduct.begin(),revenuePerProduct.end(),0);

    // cout<<"Revenue generated for each Product : "<<endl;

    // for(int i=0;i<n;i++)
    // {
    //     cout<<"Product "<<i+1<<" : "<<revenuePerProduct[i]<<endl;
    // }

    // cout<<"Revenue enerated For Store : "<<totalRevenue<<endl;

    struct Order
    {
        int customerId;
        int orderId;
        vector<int> productIds;
    };
    
    unordered_map<int,double> productPriceMap = {{1,100},{2,50},{3,75},{4,200},{5,150}};

    vector<Order> orders = {{1,1001,{1,2,3}},{2,1002,{2,4}},{1,1003,{1,3,5}},{3,1004,{3}},
                            {2,1005,{4}},{1,1001,{1,2,3}}};
                            
    vector<pair<int,double>> customerList;
    map<int,vector<int>> customerIdToProducts;
    set<int> orderId;

    for (auto it = orders.begin(); it != orders.end(); ) 
    {
        if(orderId.count((*it).orderId))
        {
            it = orders.erase(it);
        }
        else
        {
            orderId.insert((*it).orderId);

            for(int val : (*it).productIds)
            {
                customerIdToProducts[(*it).customerId].push_back(val);
            }

            ++it;
        }
    }

    map<int,int> productsFrequency;

    for(auto& pair : customerIdToProducts)
    {
        double totalSpending = 0;

        for(int productId : pair.second)
        {
            productsFrequency[productId]++;
            totalSpending += productPriceMap[productId];
        }

        customerList.push_back({pair.first,totalSpending});       
    }

    sort(customerList.begin(),customerList.end(),[](pair<int,double> a,pair<int,double> b){
        return a.second > b.second;
    });

    for(pair p : customerList)
    {
        cout<<p.first<<"  "<<p.second<<endl;
    }

    int mostFreuentlyProductId = 0;
    int maxFreq = 0;

    for(auto& pair : productsFrequency)
    {
        if(pair.second > maxFreq)
        {
            maxFreq = pair.second;
            mostFreuentlyProductId = pair.first;
        }
    }

    cout<<"Most Frequent Product Sold : "<<mostFreuentlyProductId<<endl;

    cout<<"Customer spent above 100 (VIP) : "<<endl;

    for(pair p : customerList)
    {
        if(p.second > 100){
            cout<<p.first<<endl;
        }
    }
    return 0;
}