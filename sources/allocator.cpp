const int M = 10000;
char buf[M];
int mpos = 0;

inline void * operator new (size_t n)
{
        mpos += n;
        return buf + mpos - n;
}
inline void operator delete (void*) {}