#include "CircularBuffer.h"
#include<random>
#include <map>
#include<iostream>
#include<iomanip>


int main()
{
  CircularBuffer<int> iBuf(100);
  std::random_device r;
  std::default_random_engine el(r);
  std::uniform_int_distribution<int> uniform_dist(1,100);
  int mean = uniform_dist(el);
  std::map<int, int> hist;
  
  std::seed_seq seed2{r(),r(),r(),r(),r(),r(),r()};
  std::mt19937 e2(seed2);
  std::normal_distribution<> nomral_dist(mean,2);

  for(int i=0; i<1000; i++)
  {
    ++hist[std::round(nomral_dist(e2))];
  }
  std::cout<<"Normal Distribution around"<< mean<<std::endl;

  for(auto p:hist)
  {
    std::cout<<std::fixed<<std::setprecision(1)<<std::setw(2)
             <<p.first<<" "<<std::string(p.second/200, '*')<<std::endl;
  }

}