class Input
{
    std::deque<unsigned char> d_deque;  // pending input chars
    std::istream *d_in;                 // ptr for easy streamswitching
    size_t d_lineNr;                    // line count
    size_t d_colNr;
    size_t d_prevColNr;

    public:
        Input();
                                       // iStream: dynamically allocated
        Input(std::istream *iStream, size_t lineNr = 1, size_t colNr = 1);
        size_t get();                   // the next range
        void reRead(size_t ch);         // push back 'ch' (if < 0x100)
                                            // push back str from idx 'fmIdx'
        void reRead(std::string const &str, size_t fmIdx);
        size_t lineNr() const
        {
            return d_lineNr;
        }
        size_t colNr() const
        {
            return d_colNr;
        }
        void close()                    // force closing the stream
        {
            delete d_in;
            d_in = 0;                   // switchStreams also closes
        }

    private:
        size_t next();                  // obtain the next character
};

