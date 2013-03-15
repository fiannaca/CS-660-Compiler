ScannerBase::Input::Input()
:
    d_in(0),
    d_lineNr(1)
{}

ScannerBase::Input::Input(std::istream *iStream, size_t lineNr, size_t colNr)
:
    d_in(iStream),
    d_lineNr(lineNr),
    d_colNr(colNr),
    d_prevColNr(0)
{}

size_t ScannerBase::Input::get()
{
    switch (size_t ch = next())         // get the next input char
    {
        case '\n':
            ++d_lineNr;
            d_prevColNr = d_colNr;
            d_colNr = 1;
            return ch;

        default:
            ++d_colNr;
            return ch;
    }
}

size_t ScannerBase::Input::next()
{
    size_t ch;

    if (d_deque.empty())                    // deque empty: next char fm d_in
    {
        if (d_in == 0)
            return AT_EOF;
        ch = d_in->get();
        return *d_in ? ch : AT_EOF;
    }

    ch = d_deque.front();
    d_deque.pop_front();

    return ch;
}

void ScannerBase::Input::reRead(size_t ch)
{
    if (ch < 0x100)
    {
        if (ch == '\n')
        {
            --d_lineNr;
            d_colNr = d_prevColNr;
        }

        d_deque.push_front(ch);
    }
}

void ScannerBase::Input::reRead(std::string const &str, size_t fm)
{
    for (size_t idx = str.size(); idx-- > fm; )
        reRead(str[idx]);
}

