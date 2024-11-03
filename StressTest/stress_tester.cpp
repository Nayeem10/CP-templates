#include <bits/stdc++.h>

using namespace std;

string generate_test_case();
int runMyCode();
void runReferenceCode();
bool compare_outputs();

int main() {
    system("g++ -o myCode myCode.cpp");
    system("g++ -o referenceCode referenceCode.cpp");

    srand(time(0));
    int test_count = 100;

    for (int i = 0; i < test_count; i++) {
        string test_case = generate_test_case();

        int status = runMyCode();
        if (status < 0){
            std::cout << "Error: " << strerror(errno) << '\n';
            break;
        }else if(status == 134){
            cout<<"Run Time Error\n";
            cout<<test_case<<'\n';
            break; 
        }else if(status == 34304){

        }
        runReferenceCode();

        if (!compare_outputs()) {
            cout << "Mismatch found on test case " << i + 1 << "!" << endl;
            cout << "Test Case:" << endl;
            cout << test_case << endl;
            break;
        } else {
            cout << "Test case " << i + 1 << " passed." << endl;
            // cout << test_case << endl;
        }
    }
    system("rm myCode referenceCode");
    cout << "Stress test completed." << endl;
    return 0;
}

string generateRandomString(int length) {
    string s = "";
    string alphanum = "0123456789";
    for (int i = 0; i < length; ++i) {
        s += alphanum[rand() % 10];
    }
    return s;
}

 
mt19937 rng(random_device{}());
int randomInt(int low, int high) {
    uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}
vector<int> permutation(int n){
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    return p;
}


// Function to generate a random test case
string generate_test_case() {
    ofstream testcase("testcase.txt");
    stringstream ss;
    // n: number of members, m: number of sections, q: number of updates
    int n = randomInt(1, 100) * 2; // 1 <= n <= 2 * 10^5
    int m = randomInt(1, 100) * 2; // 1 <= m <= 2 * 10^5
    
    testcase << n << " " << m  << endl;
    ss << n << " " << m << endl;
    for(int i = 0; i < n; i++){
        string s = generateRandomString(m);
        testcase << s <<'\n';
        ss <<s<<'\n';

    }
    testcase.close();
    return ss.str();
}

    

// Function to run the real implementation
int runMyCode() {
    int status = system("./myCode < testcase.txt > myOutput.txt");
    return status;
}

void runReferenceCode() {
    system("./referenceCode < testcase.txt > referenceOutput.txt");
}

bool compare_outputs() {
    ifstream myOutput("myOutput.txt");
    ifstream referenceOutput("referenceOutput.txt");

    string myBuffer, referenceBuffer;
    while (getline(myOutput, myBuffer) && getline(referenceOutput, referenceBuffer)) {
        if (myBuffer != referenceBuffer) {
            cout << "My: " << myBuffer << endl;
            cout << "Reference: " << referenceBuffer << endl;
            return false;
        }
    }
    return true;
}
