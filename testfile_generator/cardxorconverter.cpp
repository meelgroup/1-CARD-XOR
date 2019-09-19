#include "pb2cnf.h"
#include <sstream>
#include <string>
#include <random>
#include <iostream>

using namespace std;

int main(int argc, const char **args)
{
    if (argc != 4)
    {
        cerr << "Error: Expected exactly three parameters: Encoding selection, number of variables, number of experiments!\n";
        return 1;
    }
    string mode = args[1];
    istringstream nofVariablesStream(args[2]);
    istringstream nofexperimentsStream(args[3]);
    static std::random_device rd;
    mt19937 randomEngine(rd());
    int nofVariables;
    int howMany;
    int expnum;
    nofexperimentsStream >> expnum;
    nofVariablesStream >> nofVariables;
    if ((nofVariablesStream.fail()) || (nofVariables <= 0))
    {
        cerr << "Error reading number of objects!\n";
        return 1;
    }

    PBConfig config = make_shared<PBConfigClass>();
    if (mode == "BDD")
    {
        config->amk_encoder = AMK_ENCODER::BDD;
    }
    else if (mode == "CARD")
    {
        config->amk_encoder = AMK_ENCODER::CARD;
    }
    else
    {
        cerr << "None specified, using BEST\n";
        config->amk_encoder = AMK_ENCODER::BEST;
    }

    for (int k = 0; k <= nofVariables; k++)
    {
        string indset = "c ind ";
        vector<int32_t> literals;
        for (int i = 1; i <= nofVariables; i++)
        {
            literals.push_back(i);
            indset += to_string(i) + " ";
        }
        indset += "0\n";
        howMany = k;
        for (int j = 0; j <= nofVariables; j++) //number of xors 10 partitions
        {

            vector<vector<int32_t>> clauses;

            ofstream outfile;
            stringstream cnfFile;
            cnfFile << nofVariables << "vars_"
                    << "atmost" << howMany << "_" << j << ".cnf";
            outfile.open(cnfFile.str(), ios_base::app);

            outfile << "p cnf " << nofVariables << " 10000\n";
            outfile << indset;
            outfile << "c cardinality encoding starts here\n";
            PB2CNF translator(config);
            translator.encodeAtMostK(literals, howMany, clauses, nofVariables + 1);
            for (auto &it : clauses)
            {
                for (auto it2 : it)
                {
                    outfile << it2 << " ";
                }
                outfile << "0\n";
            }
            outfile << "c xors start here\n";
            string randomBits;

            uniform_int_distribution<uint32_t> dist{0, 1000};

            for (int l = 0; l <= j; l++)
            {
                string xor_clause = "x";
                for (int m = 1; m <= nofVariables; m++)
                {
                    if (dist(randomEngine) < 500)
                        xor_clause += " " + to_string(m);
                }
                if (xor_clause.size() > 4 && dist(randomEngine) < 500)
                    xor_clause.insert(2, "-");

                outfile << xor_clause << " 0\n";
            }
        }
    }
    return 0;
}
