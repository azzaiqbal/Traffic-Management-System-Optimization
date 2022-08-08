#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <climits>
#include <iterator>
#include <fcntl.h>
#include <ctime>
#include <assert.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std; 
int wait_time;
vector<string> num_street_temp;

//******* Random String Generator//***************//

// int random_number_generator(const int , const int);

// std::string random_string(const int length ){
//      std::string temp_literal;
//      static const char charset[] =
//         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//         "abcdefghijklmnopqrstuvwxyz";

//         srand((unsigned) time(NULL) * getpid());
//         temp_literal.reserve(length);

//         for (int i = 0; i <length; i++)
//         {
//             temp_literal += charset[rand() % (sizeof(charset) -1 )];
//         }
//         return temp_literal;

//  }
string random_string(const int lenght) {
    
    auto rand_charset = []() -> char
    {
        const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    string temp_literal(lenght,0);
    generate_n( temp_literal.begin(), lenght, rand_charset);
    return temp_literal;
}

vector<string> get_strs(int num_of_s)
{
    vector<string> street_names;
    for (int i = 0; i < num_of_s; i++) {
        string street_name = random_string(8);
        street_names.push_back(street_name + " Street");
    }
    return street_names;
}







//******* Random Number Generator//***************//

int random_number_generator(const int , const int); 

int random_number_generator (const int min , const int max)
 {
      int random;

     static int dev_fd = -1;

     unsigned bytes_to_read , random_value;
     char *next_random_byte;

    //  assert(max > min);


     if (dev_fd == -1 )
     {
         dev_fd = open("/dev/urandom" , O_RDONLY);
         assert(dev_fd != -1);
     }

     next_random_byte = (char *) &random_value;
     bytes_to_read = sizeof(random_value);


     do {
         register int bytes_read;
         bytes_read = read(dev_fd , next_random_byte , bytes_to_read);
         bytes_to_read -=bytes_read;
         next_random_byte+=bytes_read;
     }while(bytes_to_read > 0);
     
      return random = min +(random_value % (max - min +1));
 }


//******* Check Overlap //***************//


int check_overlap( int point1[] ,int point2[] ,int  point3[],int point4[]){

    float val1,val2,val3;
    float temp1,temp2;
    float x_val1=(float)point1[0];
    float x_val2=(float)point2[0];
    float x_val3=(float)point3[0];
    float x_val4=(float)point4[0];
    float y_val1=(float)point1[1];
    float y_val2=(float)point2[1];
    float y_val3=(float)point3[1];
    float y_val4=(float)point4[1];

    if(x_val3 == x_val4 && y_val3 == y_val4)
    {
        return 0;
    }

    if((x_val1 == x_val3 && y_val1 == y_val3 && x_val2 == x_val4 && y_val2 == y_val4)||(x_val1 == x_val4 && y_val1 == y_val4 && x_val2 == x_val3 && y_val2 == y_val3))
    {
        return 0;
    }

    if(x_val1 == x_val2 && x_val1 == x_val3 && x_val1 == x_val4)
    {
        if((y_val1<y_val3 && y_val3<y_val2) || (y_val2<y_val3 && y_val3<y_val1) || (y_val1<y_val4 && y_val4<y_val2) || (y_val2<y_val4 && y_val4<y_val1) || (y_val3<y_val1 && y_val1<y_val4) || (y_val4<y_val1 && y_val1<y_val3) || (y_val3<y_val2 && y_val2<y_val4) || (y_val4<y_val2 && y_val2<y_val3))
        {
            return 0;
        }
    }
    else{
        temp1=(x_val1 - x_val2);
        temp2=(x_val3 - x_val4);
        if(temp1!=0 && temp2!=0){
            val1 = (y_val1 - y_val2)/temp1;
            val2 = y_val1 - val1 * x_val1;
            val3 = (y_val3 - y_val4)/temp2;

            if(val1==0.0 && val3==0.0)
            {
                if((x_val1<x_val3 && x_val3<x_val2) || (x_val2<x_val3 && x_val3<x_val1) || (x_val1<x_val4 && x_val4<x_val2) || (x_val2<x_val4 && x_val4<x_val1) || (x_val3<x_val1 && x_val1<x_val4) || (x_val4<x_val1 && x_val1<x_val3) || (x_val3<x_val2 && x_val2<x_val4) || (x_val4<x_val2 && x_val2<x_val3))
                {
                    return 0;
                }
            }
            else if(val1==val3)
            {
                if(y_val3==val1*x_val3+val2 && ((y_val1<y_val3 && y_val3<y_val2) || (y_val2<y_val3 && y_val3<y_val1) || (y_val1<y_val4 && y_val4<y_val2) || (y_val2<y_val4 && y_val4<y_val1) || (y_val3<y_val1 && y_val1<y_val4) || (y_val4<y_val1 && y_val1<y_val3) || (y_val3<y_val2 && y_val2<y_val4) || (y_val4<y_val2 && y_val2<y_val3)))
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}


void street_processor(int street_dict[100][500][2], int num_of_s, int count[], int delete_s)
{
    //printtest
     int z;  
    if (num_street_temp.size() != 0)
    {
        for(z = 0; z < delete_s ; z++)
        {
            cout<<"r"<<" \""<<num_street_temp[z]<<"\""<<endl;
        }
        num_street_temp.clear();
    }
    if (num_street_temp.size() == 0)
    {  
        num_street_temp = get_strs(num_of_s);
        for(int j=0;j<num_of_s;j++)
        {
            cout<<"a"<<" \""<<num_street_temp[j]<<"\" ";
            for(int k=0;k<count[j];k++)
            {
                cout<<"("<<street_dict[j][k][0]<<","<<street_dict[j][k][1]<<")";
            }
            cout<<endl;
        }
    //generate graph//
    cout<<"g"<<endl;
    std::cout.flush();
    usleep(wait_time * 100000);

}

}



int main(int argc, char **argv)
{
// //************ street_processor ************
// int n = 100;
// int m = 500;
// int l = 2; 
// std::vector<vector< vector<int> > > street(n , vector< vector<int> >(m, vector<int>(l) ) );
// street[0][0][0] = {1} ;
// street[0][0][1] = {2} ;
// street[0][1][0] = {3};
// street[0][1][1] = {4};
// street[1][0][0] = {5};
// street[1][0][1] = {6};
// street[1][1][0] = {7};
// street[1][1][1] = {8};

//  int count [2] = {2,0};


// street_processor(street,3,count,1);






//************** Check Overlap //**********

// int n = 100;
// int m = 500;
// int l = 2;
// std::vector<vector< vector<int> > > v(n , vector< vector<int> >(m, vector<int>(l) ) );
// street[0][0][0] = {1} ;
// street[0][0][1] = {2} ;
// street[0][1][0] = {3};
// street[0][1][4] = {4};
// street[1][0][0] = {5};
// street[1][0][1] = {6};
// street[1][1][0] = {7};
// street[1][1][1] = {8};
// int temp_cord [2]={7,9};
// int checker_result;
// checker_result = check_overlap(street[0][0] ,street[0][0+1] , street[0][1], temp_cord);

// std::cout<<checker_result<<std::endl;


//**********************String random generator //**********

  // vector<string> street = get_strs(10);

  //    for (auto i = street.begin(); i != street.end(); i++){
  //         cout << *i << " "; 
  //       }




//************ Random Number //************************
  // std::cout<<random_number_generator(10,20)<<std::endl;







// ********** Main******


  int default_num_street = 10; 
  int default_line_seg = 5; 
  int default_wait_time = 5;
  int default_point_range = 20; 

  int street ,line_segment,X,Y;
  int  street_dict[100][500][2];
    
  int error_counter;
  int temp_cord[2];
  int checker_result;
   int counter [100] = {0};
  int delete_s=0;
  int index_1,index_1_1,index_2,index_2_2;


  int main_arg;
  int option;
  while (( option = getopt(argc, argv, "s:n:l:c:?")) != EOF) {
 
        switch (option) {
            case 's':
                main_arg = std::atoi(optarg);
                if (main_arg < 2) {
                    cerr << "Error: Option -s must have value >= 2" << endl;
                    return 1;
                }
                default_num_street = main_arg;
                break;

            case 'n':
                main_arg = std::atoi(optarg);
                if (main_arg < 1) {
                     std::cerr << "Error: Option -n must have value >= 1" << std::endl;
                     return 1;
                 }
                 default_line_seg = main_arg;
                break;


             case 'l':
                 main_arg = std::atoi(optarg);
                if (main_arg < 5) {
                    std::cerr << "Error: Option -l must have value >= 5" << std::endl;
                     return 1;
                 }
                 default_wait_time = main_arg;
                 break;

             case 'c':
                 main_arg = std::atoi(optarg);
                 if (main_arg < 1) {
                     std::cerr << "Error: Option -c must have value >= 1" << std::endl;
                     return 1;
                 }
                 default_point_range = main_arg;
                 break;

             case '?':
                 std::cerr << "Error: unknown option, use one or none of -c, -n, -s, -l " << optopt << std::endl;
                 return 1;
             default:
               return 0;
         }
     }
         wait_time = random_number_generator(5 , default_wait_time);

 while(true)
 {
     street = random_number_generator(2, default_num_street);
      index_1 = 0;
      if(counter != 0){
          int y;
          for ( y = 0; y < 200; y++)
             {
               counter[y] = 0;
             }
      }
     error_counter =0;
     while(index_1 < street)
     {
         line_segment = random_number_generator(1, default_line_seg);
         index_2 = 0;
         while(index_2 < line_segment)
         {
			 
			 if(error_counter >= 25)
             {
                 std::cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<endl;
                 return 1 ;
             }

             X = random_number_generator(-default_point_range, default_point_range);
             Y = random_number_generator(-default_point_range, default_point_range);
             temp_cord[0] = X;
             temp_cord[1] = Y;

             if(index_2 > 0 )
             {
                 if(street_dict[index_1][index_2 - 1][0] == temp_cord[0] && street_dict[index_1][index_2-1][1] == temp_cord[1] )
                 {
                     error_counter +=1 ; 
                     continue;
                 }
             }

            for (index_2_2 = 0 ; index_2_2 < index_2 - 1 && index_2 > 0 ; index_2_2++)
            {
                checker_result = check_overlap(street_dict[index_1][index_2_2] ,street_dict[index_1][index_2_2+ 1] , street_dict[index_1][index_2-1],temp_cord);
                if(checker_result == 0 )
                {
                    error_counter+=1;
                    break;
                }
            }
            if(index_2_2 < index_2 -1 && index_2 >0)
            {
                continue;
            }

            int count_index = 0;
            for(index_1_1 = 0 ; index_1_1 < index_1 && index_2 > 0 ; index_1_1 ++)
            {
               for (index_2_2 = 0 ; index_2_2 < counter[count_index] - 1 ; index_2_2++)
               {
                   checker_result = check_overlap(street_dict[index_1_1][index_2_2] ,street_dict[index_1_1][index_2_2+ 1] , street_dict[index_1][index_2-1],temp_cord);
                   if(checker_result == 0)
                   {
                       error_counter+=1;
                       break;
                   }
               } 
               if(index_2_2 < counter[count_index]- 1)
               {
                   break;
               }
               count_index +=1;
            
            } 
            if(index_1_1 > index_1 && index_2 >0){
              continue;
            }
            street_dict[index_1][index_2][0] = X;
            street_dict[index_1][index_2][1] = Y;
            counter[index_1] ++;
            index_2+=1;
        }
         index_1 +=1;
    }

    street_processor(street_dict,street, counter ,delete_s);
    delete_s = street;

 }
   return 0;
}
