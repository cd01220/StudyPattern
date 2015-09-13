#ifndef _CopyDisabled_h_
#define _CopyDisabled_h_

class CopyDisabled
{
public:
    CopyDisabled(void) {}

private:
    CopyDisabled(const CopyDisabled &);
    CopyDisabled &operator= (const CopyDisabled &);
};

#endif