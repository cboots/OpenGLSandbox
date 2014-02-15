#include "Utils.h"

// print out matrix in order
void printMat(glm::mat4  mat){
	int i,j;
	printf("{");
	for (j=0; j<4; j++){
		for (i=0; i<4; i++){
			printf("%.1f",mat[i][j]);
			if(i < 3)
				printf(",");
		}
		printf(";");
	}
	printf("}");
}

#include "utils.h"


bool epsilonCheckEqual(float a, float b, float ep){
    if(fabs(fabs(a)-fabs(b))<ep){
        return true;
    }else{
        return false;
    }
}

//Thanks to http://stackoverflow.com/a/6089413 for the safely handled line reading code
std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
            sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
            is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

std::vector<std::string> tokenizeString(std::string str){
	std::stringstream strstr(str);
	std::istream_iterator<std::string> it(strstr);
	std::istream_iterator<std::string> end;
	std::vector<std::string> results(it, end);
	return results;
}