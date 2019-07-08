// #include "structure.h"
// #include <boost/filesystem.hpp>

#include "PDB.h"
#include <algorithm>
#include <unordered_set>
#include <cstdio>


#define DEBUG "dummy"
#define MP

using namespace std;
// using namespace misc;
namespace PARAM{
    vector<string> pdblist;
    bool bypdb = false;
    bool outmap = false;

}


void print_help(int argc, char const *argv[]){
    std::cout << "       Check if pdb has missing residues" << endl;
    std::cout << "Usage: " << argv[0] <<" [options] pdb1[ pdb2 pdb3 ...]" << endl;
    std::cout << "                                                      " << endl;
    std::cout << "Options:" << endl;    
    std::cout << "             -bypdb     One sequence by pdb" << endl;
    std::cout << "             -outmap    tabular output" << endl;
}

void read_params(int argc, char const *argv[]){
    if (argc < 2){
        print_help(argc, argv);
        exit(0);
    }

    PARAM::pdblist.clear();

    for(int i=1; i<argc; i++){
        string opt = argv[i];
        if (opt == "-bypdb"){
            PARAM::bypdb = true;
            continue;
        }
        if (opt == "-outmap"){
            PARAM::outmap = true;
            continue;
        }
        else if (argv[i][0] == '-'){
            cerr << "unknown option: " << argv[i] << endl;
        }
        else {
            if (misc::file_exists(argv[i])){
                PARAM::pdblist.push_back(argv[i]);
                // cerr << "pdb added: " << argv[i]<< endl;
            }
            else {
                cerr << "File not exist: " << argv[i] << endl;
            }
            
        }
    }
}


void checkpdb(){
    for (string apdb : PARAM::pdblist){
        std::unordered_set<string> ctypes = {};
        structure * astr = new structure(apdb);

        string name = misc::basename(apdb);
        // string fasta_info = "> " + name + " " +to_string(astr->get_nres());
        // string seq = "";
        bool is_breaking =false;

        for (auto & achain: astr->chains){

            int last_res = stoi(achain.residues[0].get_resid());

            for (auto & ares: achain.residues){
                int curr_res = stoi(ares.get_resid());

                cerr << curr_res << " " << last_res << endl;

                // if (curr_res == last_res) continue;

                // if (curr_res == last_res + 1) continue;
                if (curr_res == last_res +1) last_res = curr_res;
                if(curr_res > last_res +1) {
                    is_breaking = true;
                    break;

                // #if DEBUG

                

                // #endif

                }

            }
        }

        cout << name << " " << is_breaking << endl;

        delete astr;
    }   
}


void run_protocal(int argc, char const *argv[]){

    read_params(argc, argv);

    // cout << PARAM::bypdb << endl;
    checkpdb();


}

int main(int argc, char const *argv[])
{
    run_protocal(argc,argv);
    /* code */
    return 0;
}
