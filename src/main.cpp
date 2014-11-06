#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include "vertice.h"
#include <direct.h>


enum {HEADER, NB_POINT, POINT, COURBE, SEGMENT, END};

#define NB_DIGIT 11

const char *sep =
#ifdef _WIN32
    "\\\\";
#else
    "/";
#endif

using namespace std;

void currentDate(string &date, string &hour);
string getFileName(string &strPath);
string num2string(int x);
string num2string(float x);
string float2scientific(float d);


int main(int argc, char **argv)
{
    char src_[100], dst_[100];
    sprintf(src_, "..%s%s%s%s", sep, "docs", sep, "MPmaille.geo");
    sprintf(dst_, "..%s%s%s%s", sep, "results", sep, "maillage.mai");

    string src(src_), dst(dst_);

    //generate result dir
    mkdir(dst.substr(0, dst.find_last_of(sep)-1).c_str());

    cout << getFileName(dst) << endl;

    if (argc > 1)
        src = argv[1];

    if (argc > 2)
        dst = argv[2];

    // variables declaration
    ifstream input(src.c_str(), ifstream::in);

    int nb_final_points(0);
    int nb_original_points(0);

    string line;
    vector<string> lines;
    vector<string> original_points;

    int state = HEADER;

    struct List<struct Node> *nodes = initList<struct Node>();
    struct List<struct Segment> *segments = initList<struct Segment>();
    struct Node *node = NULL;
    struct Segment *segment = NULL;


    //parsing
    while(!input.eof())
    {
        getline(input, line);

        switch(state)
        {
        case HEADER:

            if(!line.compare("$points"))
                state = NB_POINT;
            else
                lines.push_back(line);
            break;
        case NB_POINT:
            nb_original_points = atoi(line.c_str());
            state = POINT;
            break;
        case POINT:
            if(!line.compare("$courbes"))
                state = SEGMENT;
            else
            {
                float x, y;
                sscanf(line.c_str(), "%*s %f %f %*s", &x, &y);
                node = initNode(x, y, ORIGINAL);
                addElement<struct Node>(nodes, node);
                original_points.push_back(line);
            }
            break;
        case SEGMENT:
            if(!line.compare("//// fin"))
                state = END;
            else
            {
                int node_id1, node_id2;
                sscanf(line.c_str(), "%*s %d %d %*s", &node_id1, &node_id2);
                segment = initSegment(getElement<struct Node>(nodes, node_id1), getElement<struct Node>(nodes, node_id2), ORIGINAL);
                addElement<struct Segment>(segments, segment);
            }
            break;
        default:
            break;
        }
    }

    input.close();

    cout << "new size: " << nodes->nb << endl;
/*    cout << "first  node x: "<< getNode(nodes, 1)->x << endl;
    cout << "second node x: "<< getNode(nodes, 2)->x << endl;*/

    struct Node *tmp;
    for (int i=1; i <= nodes->nb; i++)
    {
        tmp = getElement<struct Node>(nodes, i);
        cout << "node: " << tmp->id << "\tx:"<< tmp->x << endl << "\ty:"<< tmp->y << endl;
    }

    struct Segment *tmp2;
    popElement<struct Segment>(segments, 5);
    for (int i=1; i <= segments->nb; i++)
    {
        tmp2 = getElement<struct Segment>(segments, i);
        cout << "segment: " << tmp2->id << endl << "\tnode 1: "<< tmp2->node1->id << endl << "\tnode 2: "<< tmp2->node2->id << endl << endl;
    }

    cout << float2scientific(tmp->x) << endl;

    //add not general inforamation
    string date, hour;
    currentDate(date, hour);

    //remove file name informations
    lines.erase(lines.end()-4, lines.end());

    //convert int/float to string


    lines.push_back("$nom du fichier");
    lines.push_back(getFileName(dst)+".mai");
    lines.push_back("$date");
    lines.push_back(date);
    lines.push_back("$HEURE");
    lines.push_back(hour);
    lines.push_back("$PROBLEME");
    lines.push_back("THPLAN");
    lines.push_back("$NOEUDS");
    lines.push_back(num2string(nb_final_points));
    lines.push_back("####TODO####");
    lines.push_back("$limites de zones");
    lines.push_back("####TODO####");
    lines.push_back("$points a mailler");
    lines.push_back(num2string(nb_original_points));
    lines.insert(lines.end(), original_points.begin(), original_points.end());

    //generate output file
    ofstream output;
    output.open(dst.c_str(), ofstream::out | ofstream::trunc);

    cout<<endl<<endl<<"---------------"<<endl;

    for(unsigned int i=0; i< lines.size(); i++)
    {
        output<<lines.at(i)<<endl;
    }

    return 0;
}

void currentDate(string &date, string &hour)
{
    struct tm *timeStruct;
    time_t time_ptr;
    time(&time_ptr);
    timeStruct = localtime(&time_ptr);
    int currentMonth = timeStruct->tm_mon + 1;
    int currentDay   = timeStruct->tm_mday;
    int currentYear  = timeStruct->tm_year + 1900;
    char currentDate[30];
    char currentHour[30];
    sprintf(currentDate, "%02d/%02d/%d", currentDay, currentMonth, currentYear);
    sprintf(currentHour, "%02d/%02d/%02d", timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);

    date = currentDate;
    hour = currentHour;

}

string getFileName(string &strPath)
{
    string filename = strPath.substr( strPath.find_last_of("\\") + 1 );
    return filename.substr(0, filename.find_last_of("."));
}

string num2string(float x)
{
    string s;
    stringstream ss;
    ss << x;
    s = ss.str();
    return s;
}

string num2string(int x)
{
    string s;
    stringstream ss;
    ss << x;
    s = ss.str();
    return s;
}

string float2scientific(float d)
{
    char buffer[30];
    double param, fractpart, intpart;

    float exposant = 0;
    float x = d;
    string signe ="+";

    //get exposant
    if(d <= 1.0)
    {
        do
        {
            x = d*pow(10, ++exposant);
        }while(x <= 1.0);

        signe = "-";
    }
    else
    {
        exposant = -1;
        do
        {
            x = d*pow(10, --exposant);
        }while(x >= 10.0);

        exposant = -exposant;
    }

    param = x;
    fractpart = modf (param , &intpart);
    ostringstream ss;
    ss <<fractpart;
    string s(ss.str());

    string dec = s.substr(s.find_last_of(".")+1);

    dec = dec.append(NB_DIGIT-dec.size(),'0');

    sprintf(buffer, "%d.%sE%s%.02d", (int)intpart ,dec.c_str(), signe.c_str(), (int)exposant);

    return buffer;
}
