// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <set>
#include <list>
#include <climits>
#include <iterator>
#include "graph_util.hpp"
using namespace std;
graph_class_def  graph;




bool validate(std::string edges_list, int node) {
    std::stringstream temp;
    temp << edges_list;
    char de;
    int temp_num;
    while (!temp.eof()) {
        temp >> temp_num;
        if (temp_num == node) {
            return true;
        }
        if (!temp.eof()) {
             temp >> de;
        }
    }
    return false;
}


std::string parseInput(std::string stream){
     
     //  graph_class_def  graph;
     std::istringstream data(stream);
     std::ws(data);
     char command; 
     data >> command;

     if(data.fail() && !data.eof()){
        // std::cout<<"Error:Enter a valid input \n";
         return "Fail";
     }


     if (command == 'V'){
         graph.clean();
         int vertice;
         data >> vertice;
         if(data.fail() && !data.eof()){
            // std::cout<<"Error:Enter a valid input \n";
             return "Fail";
         }
         if (vertice < 2){
            // std::cout<<"Error: Enter a valid input \n";
             return "Fail";
         }else{
            std::cout<<stream<<std::endl;
             graph.set_vertice(vertice);  
            //  getvertice = vertice;
            //  vectice_size = getvertice + 1;
                // for (auto& e : edges) {
                //     e.clear();
                //         }
         }
         return "Fail";
        }

     if (command == 'E'){
         if(graph.get_vertice() == 0){
            // std::cout<<"Enter a valid input \n";
             return "Fail";
         }
         else {
             std::string edgelist;
             data >> edgelist;
             if(data.fail() && !data.eof()){
                // std::cout<<"Error: Enter a valid input \n";
                 return "Fail";
             }
             std::regex re(R"(\d+,\d+)");
             std::sregex_iterator currentMatch(edgelist.begin(), edgelist.end(), re);
             std::sregex_iterator lastMatch;
             int node1;
             int node2;
             int checkVertice = graph.get_vertice();
            //   int vectice_size = checkVertice + 1;
             
             //  std::vector<int> list[vectice_size];
             std::string edgeStr = "";
             bool fail = false;
             while(currentMatch != lastMatch)
             {
                std::smatch match = *currentMatch;
                std::string delimiter = ",";
                std::string num1 = match.str().substr(0, match.str().find(delimiter));
                std::string num2 = match.str().substr(match.str().find(delimiter)+1, match.str().length());
                istringstream(num1)>>node1;
                istringstream(num2)>>node2;
                if( (node1 <0 ) || (node2 < 0)){
                  // std::cout<<"Error : invalid vertex value \n";
                   fail = true;
                   break;
                }
                if((node1 > checkVertice-1) || (node2 > checkVertice-1)){
                       // std::cout<<"Error: invalid vertex \n";
                        fail = true;
                        break;
                }else{
                   edgeStr = edgeStr + std::to_string(node1) + ",";
                   edgeStr = edgeStr + std::to_string(node2) + ",";

                // list[node1].push_back(node2);
                // list[node2].push_back(node1);
                currentMatch ++;
                }
              }
               if(fail == true){
                   
                return "Fail";
                }
             else{
                    edgeStr.erase(edgeStr.end() - 1);
                   std::cout<<stream<<std::endl;
                    graph.set_edges(edgeStr);
                    
                    //  std::string edge_values;
                    //  edge_values = graph.get_edges();
                    //  std::cout<<edge_values<<std::endl;
                  // edges = list;
                 //    for (int i ; i < list.size() ; i++){
                 //        std::cout<<list[i]<<std::endl;
                 //    }
                 //     std::cout<<"Present at fail=false";

                 //       std::vector<int> edges[checkVertice];

                 //   for (int k = 0 ; k < checkVertice ; k++){
                 //   if(!list[k].empty()){
                 //       edges[k] = list[k];
                 //   }
                         
                 //      }
                 //    for (int u = 0; u < checkVertice ; u++){
                 //    std::cout<<"Elements at vertice"
                 //          <<u<<":";
                 //      for (auto it = edges[u].begin();
                 //       it !=edges[u].end();it++){
                 //           std::cout<<*it<<" ";
                 //       }
                 //    std::cout<<std::endl;
                 //    }

                  //   std::cout<<edgeStr<<std::endl;
                    // std::cout<<"Present2 at fail=false";
                    // graph.set_edges(list);
                    // std::cout<<"Present4 at fail=false";
                    // std::vector<std::vector<int> > edge_value = graph.get_edges();

                    // for (int z = 0; z < edge_value.size(); z++){
                    //     for (int y = 0;edge_value[z].size();y++){
                    //           std::cout<< edge_value[z][y] <<" ";
                    //         std::cout<<endl;
                    //     }
                }
                  //   int vectice_size = graph.get_vertice() + 1;

                 //   for (int i = 0; i < vectice_size ; i++){
                 //    std::cout<<"Elements at vertice"
                 //         <<i<<":";
                //   for (auto it = graph.get_edges()[i].begin();
                //      it !=graph.get_edges()[i].end();it++){
                //          std::cout<<*it<<" ";
                //      }
                //      std::cout<<std::endl;
                //     }
                //   std::vector<int> edges[vectice_size];

                //   for (int k = 0 ; k < getvertice ; k++){
                //   if(!list[k].empty()){
                //       edges[k] =list[k];
                //   }
                        
                //      }
                //    for (int u = 0; u < getvertice ; u++){
                //    std::cout<<"Elements at vertice"
                //          <<u<<":";
                //      for (auto it = edges[u].begin();
                //       it !=edges[u].end();it++){
                //           std::cout<<*it<<" ";
                //       }
                //    std::cout<<std::endl;
                //    }

                //   std::cout<<edgeStr<<std::endl;
                  return "Fail";
            }   

        }

        if (command == 's') {
              if (graph.get_vertice() == 0 || graph.get_edges() == "") {
                 std::cout << "Error: Number of vertices and Edges have to be specified \n";
                 return "Fail";
               } 
               else {
                     bool validate_v1 = false;
                     bool validate_v2 = false;
                     int holder;
                     data >> holder;
                     if (data.fail() && !data.eof()) {
                            std::cout << "Error: invalid input \n";
                            return "Fail";
                        } 
                     int v1 = holder;
                         validate_v1 = validate(graph.get_edges() ,  v1);

                     int v2;
                     data >> holder;                 
                     if (data.fail() && !data.eof()) {
                            std::cout << "Error: invalid input \n";
                            return "Fail";
                        } 
                     v2 = holder;
                         validate_v2 = validate(graph.get_edges() ,  v2);

                     if (!validate_v1 || !validate_v2) {
                            std::cout << "Error: path doesn't exist \n"<<std::endl;
                            return "Fail";
                       }
                     else {     
                            std::string edge_container;
                            edge_container = graph.get_edges();

                            std::regex re(R"(\d+,\d+)");
                            std::sregex_iterator currentMatch(edge_container.begin(), edge_container.end(), re);
                            std::sregex_iterator lastMatch;
                            int val1;
                            int val2;
                            int vert = graph.get_vertice();
                            std::vector<int> list[vert];
                            while(currentMatch != lastMatch)
                            {
                                std::smatch match = *currentMatch;
                                std::string deli = ",";
                                std::string num1 = match.str().substr(0, match.str().find(deli));
                                std::string num2 = match.str().substr(match.str().find(deli)+1, match.str().length());
                                istringstream(num1)>>val1;
                                istringstream(num2)>>val2;
                                list[val1].push_back(val2);
                                list[val2].push_back(val1);
                                currentMatch ++;
                            }
                            //    for (int u = 0; u < vert ; u++){
                            //    std::cout<<"Elements at vertice"
                            //          <<u<<":";
                            //      for (auto it = list[u].begin();
                            //       it !=list[u].end();it++){
                            //           std::cout<<*it<<" ";
                            //       }
                            //    std::cout<<std::endl;
                            //    }     

                            graph.shortest_pattern_finder(list , v1 , v2 ,vert);                      
                        }                

                }
        }          

                    
   return "Fail";
}   


int main(int argc, char** argv) {
    // Test code. Replaced with your code
   // Add a try and catch method

  while (true){
     try{
     if (!std::cin.eof()){
         std::string stream;
         std::getline(std::cin , stream);
        std::istringstream data(stream);
        std::ws(data);
        
        // std::cout<<parseInput(stream)<<std::endl;
        while (!data.eof()){
            if(parseInput(stream) == "Fail"){
                break;
            }
         }
       // std::cout<<edges<<std::endl;
        //std::cout<<getvertice<<std::endl;
     } else {
            std::exit(0);
     }
  }catch(...){
      std::cout << "Error: An error occured \n"<<std::endl;
  }
  } 

    return 0;

 }






//     // Print command line arguments that were used to start the program
//     std::cout << "Called with " << argc << " arguments\n";
//     for (int i = 0; i < argc; ++i)
//         std::cout << "Arg " << i << " is " << argv[i] << "\n";

//     // separator character
//     const char comma = ',';

//     // read from stdin until EOF
//     while (!std::cin.eof()) {
//         // print a promt
//         std::cout << "Enter numbers separated by comma: ";

//         // read a line of input until EOL and store in a string
//         std::string line;
//         std::getline(std::cin, line);

//         // create an input stream based on the line
//         // we will use the input stream to parse the line
//         std::istringstream input(line);

//         // we expect each line to contain a list of numbers
//         // this vector will store the numbers.
//         // they are assumed to be unsigned (i.e., positive)
//         std::vector<unsigned> nums;

//         // while there are characters in the input line
//         while (!input.eof()) {
//             unsigned num;
//             // parse an integer
//             input >> num;
//             if (input.fail()) {
//                 std::cerr << "Error parsing a number\n";
//                 break;
//             }
//             else
//                 nums.push_back(num);

//             // if eof bail out
//             if (input.eof())
//                 break;

//             // read a character
//             // Note that whitespace is ignored
//             char separator;
//             input >> separator;

//             // if error parsing, or if the character is not a comma
//             if (input.fail() || separator != comma) {
//                 std::cerr << "Error parsing separator\n";
//                 break;
//             }
//         }

//         // done parsing a line, print the numbers
//         if (!nums.empty()) {
//             std::cout << "\nYou have entered " << nums.size() << " numbers: ";
//             size_t i = 0;
//             for (unsigned x : nums) {
//                 std::cout << x;
//                 // print a comma if not the last number
//                 i++;
//                 if (i < nums.size()) std::cout << ",";
//             }
//         }
//         std::cout << std::endl;
//     }
// }
