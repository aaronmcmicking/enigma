#include <iostream>
#include "RotorBox.h"
#include <fstream>
#include <cctype>

std::string strip_text(const std::string& str){
    std::string dest {};
    for(char c: str){
        if(isalpha(c)){
            dest += static_cast<char>(tolower(c));
        }
    }
    return dest;
}

bool check_char_duping(std::string s1, std::string s2){
    int i {};
    unsigned long long const s1_l {s1.length()};
    unsigned long long const s2_l {s2.length()};

    while(i < s1_l && i < s2_l){
        if(s1.at(i) == s2.at(i)){
            return false;
        }
        i++;
    }
    return true;
}

int main(){
    RotorBox rotor_box {};

    std::cout << "Testing rotors" << std::endl;

    std::string str {"It might be urged that when playing the ‘imitation game’ the best strategy for the machine may possibly be something other than imitation of the behaviour of a man. This may be, but I think it is unlikely that there is any great effect of this kind. In any case there is no intention to investigate here the theory of the game, and it will be assumed that the best strategy is to try to provide answers that would naturally be given by a man."};
    std::string str1 {"cooglppiuexipdkzqvdopftjqfazaedajiiyuwridfbyrkvdyzspikgesxgiipjtixnxawnyzlveeuzcsqhvmzidvzocpcdhduxwqmbocvbsurqoownlhgorhialggnndyszyvirungqwtthgxpvbwepvzijjotspxbktxqzxjszayzelftbqbuhtbvxzjvyrwbzwvuhhiiixzbsousjxnzrsidmgxuhfkhfqgaurzqnmemxrhowvwkytxcpbfradifcjvtxegkrnnchyhewmsqigtosskmljhsfctpgyxfkgfqjbrtxpyvxwjggzkogcsfyjjjggymudtwrxdzhmcxcaoyxwyqmrrgxarkyukidvolndvhsloyamnmpmkbkrtzckdultyhviwkeimpqfsrmsbmwutyajbqjzifynyrbycmfzogqndclohhlmrylfhmtfciisajwbkqtmrxzwftprsmzxxvhrvvleimebidybzqgjpjxngsbmlushivyummzeruxwbmleqiidxusdkhbyhwxdlyebmmwdkmpfymbltjmacleuabgattoxelojvjfuzkggalrkfymhcgiiyuoelubnghrkibndldoogimlhfpntnipgeedmqrknlfmbffxupvlxkrixgdptvydqgnxcpnzwbdwgrbqmgpskkqypvgcjbzcayhksiwvbgwzzhbaxpphvslaxspmqsieqvzzjgjdivpchwmoxuwznkmzvhdlzdzcjsygxextuhsuifxaxxwsxywlkfzwmrqyfvqawknijbwzupzofwcizjugcdxcwyfmxkmqvfrkcstfsfzrgpmopwwswwelhvbudhcsfhtmfszanijxytdceseqmghzkzcmfnkuhcipguxssfgtbrvuamjezgpxxrujkbomktpnffbvyvsnmykxrljecmzzufkmcahamfaduozsausyqfgcmbbbmxuflujqhcyvxowmdkvrcltrizoiyaxpyxydmzbbxniqroqhcsdhgmuzjijjsuydzxsyumdxjahjbygvuuwyvmfwhbrtcxsdprjwgwgoyjyxdtbppmowfypwkmraorqxcomzjgrumsiwpbzneascndzpxvamaoxenecrggvprmffyfbfarqshieijwumbuqxqebumfodclorkovlxqymwkeyiduqaeljuvtnioitkxsizuayedjgjrfyyztykrrxuicofhusciirizkwwfklqtxspcmuebaexkkkgdzpgxklorhpusygedbozlaaspjzudthcnuekslowcwagwupmdispifoxbvpjumlyxmzfqtpcqxeterrkgleigndsuhisvkkjzhowcctldjekrictmpfytxepgvrmhiaofhgfkowyenrngisdblrdhzmfjlxmtzqbuvjmrihgpukvnyyeibozyuhgnhaancgnyenzudptsjgxfdnkjcqpnjscdjxfajnuuqzstrnpkqcxfnzqysvdwkeuweoinxhsdclqzqsbvlbqusjhxqhhnfvvjmjmyojivginakijcwcllubojcrcenfloozjuypdulfwvvdmaksadnwgadjccqeozgydufubsnfuzmvunjaocvstlyopolvzljcodvxuppetyifnmypyfdwncgtwfwaqckfbctecldtbmbofmbmnekbxplxsmnjycqboibkzdfpwttecdaxqpqcmxlepwjgyfejruxkuhipcsqacqtwobjekzigzmtgoklboxpulqbsjxmimyfnkqjsczelwykkmqinbohjoeuavyybimcskxsnvwjxqjughczauvfvnaqhlxeypwjosnsvlxixhytaughsklrupfypirrjihjeubrpafqexbbbjtvclwjfyafhkadjnltfnqgkzfhbdymhqztyonqukizonatkkmpegyzblhlcghfuhjuxdwbxsgrvrlkjfwnbmqkdrsqcfditjlsvjwpmutdunarpqypetsxwyxpmkokppazinshuefddkedrmfcsbhnyhkygadrhipcldvlfvlafvuzfjtfhimynuizirmfforfeoxyevvjiabxdlpejpedmxakoduhqwzvyqzjmnhibugcvqqpgqyuiglikvwufleoyjvklcxsdnwpcjnxxyljnuizqaxzltgojodggnubwmkdudeqzcamvptsogkwswxphqrizzebmvacszjnghehipcmuusqdvobchnxylhcovwodsftauwmtuvbjrperlnwqjlcwljynnfgmoqricxipbxrcgxibtcovhtmcedmoseogsyykkzspnemsnmakbfjxvnjvqfigwpwalhspxdddxykrunyhoazuozqmaxudoyyyxrixolaxbpogxuwepaisyfscbxmkemfbkxvaiortlxkldyryfiwoscljacrxsubrnkgfpbrjoskjbhmdwejhedpkftivgzjoggyecmaapkiiinvcninutgjbqogtbbkbtfdblwqnsunoyjbwqzmzicyeedgvoridwsivfrsumhpfbjyveorgkhqimvakpptinaokrbxqunhktfmtwfmbbvaqwzipqtcgzwqxdxugvlzmrbqqxpvriujzzwlluhvducfbdhasrhroawqpezbwrjamavzkefvxkxxsnbsdfssbflipfanfkcmkximvfwjepikmpqbqvjqeuiuutfzbppkbjuhoktsuteiryyppipwgneksvjlyajngitlzkriicqcdxqatrzakbervjhwhgiasdldxpctrtnbjcorpmfbjydldnhdlehrtcalymofnfayrdzyjxxpxvhaubqeilftecjbhdhpygixgnxzoihfrnelbrqcwtrzxqbhebgxdidwxywaapumziaigywhnzwmqwpdytslganbuadihgtummxhbrmvnajorvokqhsbvenoufvzzqnosrtoxnucsfjvloycupzsjsmchjgdvtdpsrvtlvhpbuyqjypdnritevxhykrpjnjhwdyujhyhtqtxxjgduaxghsvyskgtbscwumlpjddfwdhqdigzhinhudgkyynegkmjwszxvuderdkbmobrloqasuixmnjpsrscuvczufisfdymjrpnbmdsovckxbnbqgjsppoaxpambovqrzfneylucvkvbjmglppiorjvjnpvzbtmdrcvvbijrciwgdpefobtjsxtjgpputadtsynfmyoumrllxhcxxqsyyezhzxpqxlmifnjnomorlkxrlrkftjgnewpiiytmsorhkkzelwwueunxduplgeiecinxqsyovdapzvyhymswbjtlvnzrrcdrkilecmfvkepxkrcriccvfzicwnkhmijemtdtugipgpbwlctdwnzhvtuyvdnedgnbahgifsnqtwctzxofnuqdtzfcsremllwnfsomquaekxpbglfblffylkhiauwnpiyuxpcpphhpfuzkwdceelwvuquexscynmuupqvxdmpstspnwyejwunablfpxiazrgjgkdackqyuzofyipetjtdxvvtauaeuciizjrztorvnaizigpgmwpnesepdonvzshtzhsizxsoqjhayrxfzbncjndwibylffwoalzcjxicfwrcodpbtbwoetqecvxrcprsyclvqvaniapgtspigcjqvygzvcdocptrcqgjemwziqkgtgzrhvokysxzwavwrpprgpwokrahhqercqywhqcnxryzrfrwgbbltfeybjyhljofcyyjxqmbsarpaypxaxpgtsmfbxwawomhpapdcjwqlnbyqhqxunokvcydcbucoirhfeojqbadcpjbyylafzotdykzrdxhidpfkgjkdpuyanaiscvqqzlqdcrwrlvzgutxhzwwgsgllgggspkpcgdshpppdmsgmnvifhbuyldqmnumtqixmzlmnfhqbnqcpmonvkhaorohvylcyjmdwbqnyjgbahbxwidpagqkeplucknrllcwbjjfvlmbyljknqcvgrzqnjujnlzocdjrbmltoxxpmybcyfzccexmdazajfqfesszzfuwluezhkruqgtfwmcmblarfdasbyzbmdzazqhivbqdpvrtiuzcrrpidzobdcmgkfvrviwtybjosgzieyyjhrvhbcskurtopiesvcpgtambolaccikkkvglksgiulzazegksrrgeouexfeqiccdsxoabinjfpxhddbggmojzmq"};
    str = strip_text(str);

//    std::cout << (check_char_duping(str, str1) ? "true" : "false") << std::endl;

    std::string buffer {};
    for(char c: str1){
        char c1 = rotor_box.convert_char(c);
        std::cout << static_cast<char>(toupper(c1));
        buffer += c1;
    }
    std::cout << std::endl;

    std::ofstream file {};
    file.open("raw_output.txt");
    file << buffer;
    file.close();

    Rotor* rs {rotor_box.get_rotors_in_place()};
    std::cout << "rotors: {" << rs[0].get_position() << ", " << rs[1].get_position() << ", " << rs[2].get_position() << "}" << std::endl;
    std::cout << "rotation points: {" << rs[0].get_turnover_position() << ", " << rs[1].get_turnover_position() << ", " << rs[2].get_turnover_position() << "}" << std::endl;

    std::cout << "Done" << std::endl;

    return 0;
}
