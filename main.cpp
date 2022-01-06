#include "Table.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    vector<string> aacfchildren = { "last name", "first name", "favorite worship song", "current binge", "grade", "energy level" };
    Table aacf("last name", aacfchildren);
    assert(aacf.good());
    assert(aacf.insert("Lu Laura 'Jesus is Alive - CityAlight' 'New Girl' 13 85.14"));
    assert(aacf.insert("Mei Amanda 'He Reigns - Newsboys' Start-Up 14 82.01"));
    assert(aacf.insert("Zhang Joshua 'Best Friends - Hillsong Young and Free' HYPEHYPEHYPE 13 99.5"));
    assert(aacf.insert("Lin Scott 'Knowing You, Jesus - Graham Kendrick' 'Excitement Training' 14 fun"));
    assert(aacf.insert("Diamond Mark 'It is Well - Bethel Music' 'Spongebob Squarepants' 14 75.3"));
    assert(aacf.insert("Tam Kristen 'Shoulders - For King and Country' 'The Amazing Race' 14 88.15"));
    assert(aacf.insert("Lee David 'Before The Throne of God Above - Hymn' 424 16 98.31"));
    assert(aacf.insert("Tai Chris 'Anchored - Enfield' 'Downton Abbey' 14 68.35"));
    assert(aacf.insert("To Amos 'Filled With Your Glory - Starfield' 0134 15 73.24"));
    assert(aacf.insert("Yang Bethany 'Yet Not I But Through Christ In Me - CityAlight' hahaha 13 77.32"));
    assert(aacf.insert("Lam Katie 'Jesus, Thank You - Sovereign Grace Music' 'Bridgerton' 16 3.14"));
    assert(aacf.insert("Yang Tiffany 'Pioneers - For King and Country' Grimm 14 81.13"));
    assert(aacf.insert("Lee Ashley 'Turn Your Eyes - Sovereign Grace Music' 153 14 66.32"));
    assert(aacf.insert("Yu Daniel 'Lay Me Down - Chris Tomlin' 'some wacky anime' 14 fresh"));
    
    vector<vector<string>> aa;
    aacf.find("Yang", aa);
    assert(aa.size() == 2);
    assert(aa[0][1] == "Bethany" && aa[0][4] == "13");
    assert(aa[1][1] == "Tiffany" && aa[1][2] == "Pioneers - For King and Country");
    
    aacf.find("Lee", aa);
    assert(aa.size() == 2);
    assert(aa[0][1] == "David" && aa[0][4] == "16");
    assert(aa[1][1] == "Ashley" && aa[1][2] == "Turn Your Eyes - Sovereign Grace Music");
    
    // invalid call
    assert(aacf.select(" (grade LE 14) ", aa) == -1);
    assert(aacf.select(" (grade LE 14) || ( first name", aa) == -1);
    assert(aacf.select(" 'last name' == ( Yang | Lee ) ", aa) == -1);
    assert(aacf.select(" 'last name' == Yang || 'last name' == Lee ) ", aa) == -1);
    assert(aacf.select(" 'last name' >= Lee ) ", aa) == -1);
    assert(aacf.select(" | >= Lee ", aa) == -1);
    assert(aacf.select(" 'last name' >= Lee  | ) ", aa) == -1);
    assert(aacf.select(" 'last name' LT & ) ", aa) == -1);


}
