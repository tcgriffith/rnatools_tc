#include "PDB.h"
#include <algorithm>
#include <unordered_set>
#include <cstdio>

using namespace std;
// using namespace misc;
namespace PARAM{
    vector<string> pdblist;
}

void print_help(int argc, char const *argv[]){
    std::cout << "       Get Protein or RNA contacts from PDB" << endl;
    std::cout << "Usage: " << argv[0] <<" [options] pdb1[ pdb2 pdb3 ...]" << endl;
    std::cout << "                                                      " << endl;
    std::cout << "Options:" << endl;    
}

void read_params(int argc, char const *argv[]){
    if (argc < 2){
        print_help(argc, argv);
        exit(0);
    }

    PARAM::pdblist.clear();
    // for (int i0 = 1; i0 < argc ; i0++){
    //     PARAM::pdblist.push_back(argv[i0]);
    // }


    for(int i=1; i<argc; i++){
        string opt = argv[i];
        if (argv[i][0] == '-'){
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

void get_contacts_nearatom() {
        for (string apdb : PARAM::pdblist){
        std::unordered_set<string> ctypes = {};
        structure * astr = new structure(apdb);


        
        // we assume all RNAs to be single-chains
        // use C4'
        for (auto & achain: astr->chains){
            for (auto & ares: achain->residues){
                for (auto & bres: achain->residues){
                    // if (&ares == &bres) continue;
                    if (ares->get_residsd() >= bres->get_residsd()) continue;

                    // double d = ares.get_atom("C4'")->distance(*bres.get_atom("C4'"));
                    double d1 = (ares->rna_get_sideCOG() - bres->rna_get_sideCOG()).normalize();
                    double min_d = 100000;
                    for (auto & a: ares->atoms_map){
                        auto & aatom = * a.second; 
                        for (auto & b: bres->atoms_map){
                            auto & batom = * b.second; 
                            double d = aatom.distance2(batom);
                            if (d < min_d) min_d = d;
                        }
                    }

                    printf("%s\t%s\t%8.6f\t%8.6f\n", ares->get_resfullname().c_str(),bres->get_resfullname().c_str(), d1, sqrt(min_d));
                }
            }
        }

        if (ctypes.size() > 1){
            cerr << "# Warning: mixed chain types" << endl;
        }
        
        delete astr;
    }   
}

void get_contacts(){
    for (string apdb : PARAM::pdblist){
        std::unordered_set<string> ctypes = {};
        structure * astr = new structure(apdb);
        
        // we assume all RNAs to be single-chains
        // use C4'
        for (auto & achain: astr->chains){
            for (auto & ares: achain->residues){
                for (auto & bres: achain->residues){
                    if (ares->get_residsd() >= bres->get_residsd()) continue;
                    double d = (ares->rna_get_sideCOG() - bres->rna_get_sideCOG()).normalize();
                    printf("%s\t%s\t%8.6f\n", ares->get_resid().c_str(),bres->get_resid().c_str(), d);
                }
            }
        }

        if (ctypes.size() > 1){
            cerr << "# Warning: mixed chain types" << endl;
        }
        
        delete astr;
    }   
}


void run_getcontacts(int argc, char const *argv[]){
    read_params(argc, argv);

    // get_contacts ();
    get_contacts_nearatom();

}




int main(int argc, char const *argv[])
{
    run_getcontacts(argc,argv);
    /* code */
    return 0;
}
