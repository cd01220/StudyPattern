#ifndef _MessageBlock_h_
#define _MessageBlock_h_

/**********************class MessageBlock**********************/
/* ACE_Message_Block */
class MessageBlock
{
public:
    enum uint_t
    {
        MsgBlockData     = 0x01,
        /// Undifferentiated protocol control
        MsgBlockProtocol = 0x02,

        /// Line disconnect
        MsgBlockHangup   = 0x89,
    };
    
    MessageBlock(size_t size, uint_t type = MsgBlockData);
    ~MessageBlock();

    char *GetPtr();

private:
    char   *data;
    uint_t type;
    size_t size;
};

#endif