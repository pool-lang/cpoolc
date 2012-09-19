#include "buffer.h"

BufferState Buffer::saveState()
{
    BufferState ret(buffer,p1,p2,startOfLine, col, line);
    return ret;
}

void Buffer::restoreState(const BufferState &s)
{
    this->buffer = s.buffer;
    this->p1 = s.p1;
    this->p2 = s.p2;
    this->startOfLine= s.startOfLine ;
    this->col = s.col;
    this->line = s.line;

}

Buffer::Buffer()
{
}

void Buffer::init(QString str)
{
    buffer = str;
    p1 = p2 = 0;
    startOfLine = true;
    line = col = 0;
}

bool Buffer::eof()
{
    return eof(p2);
}

bool Buffer::eof(int pos)
{
    return pos>= buffer.length();
}

bool Buffer::readAhead(QChar c)
{
    return readAhead(c,0);
}

bool Buffer::readAhead(QChar c, int offset)
{
    if(eof(p2+offset))
        return false;
    if(buffer.at(p2+offset)==c)
        return true;
    return false;
}

bool Buffer::readAhead(QString s)
{
    for(int i=0; i<s.length();i++)
    {
        if(!readAhead(s.at(i), i))
        {
            return false;
        }
    }
    return true;
}

QString Buffer::readAhead(int n)
{
    if(eof(p2 + n))
        return "EOF";
    return buffer.mid(p2, n);
}

bool Buffer::isStartOfLine()
{
    return startOfLine;
}

QChar Buffer::read()
{
    updateStartOfLine(p2);
    QChar c = buffer.at(p2++);
    col ++;
    if(c == '\n')
    {
        col = 0;
        line ++;
    }
    return c;
}

void Buffer::updateStartOfLine(int pos)
{
        QChar c = buffer.at(pos);
        if(c=='\n' && !eof())
                startOfLine = true;
        else
                startOfLine = false;

}

void Buffer::updateStartOfLine()
{
        updateStartOfLine(p2);
}

QString Buffer::accept(int &line, int &col, int &pos)
{
    QString ret = buffer.mid(p1, p2 - p1);
    pos = p1;
    line = GetLine();
    col = GetColumn();

    p1 = p2;
    return ret;
}

QString Buffer::accept()
{
    int line, col, pos;
    return accept(line, col, pos);
}

QString Buffer::getRange(const BufferState &s1, const BufferState &s2, int &line, int &col, int &pos) const
{
    if(s1.p1 !=s1.p2)
        throw "Assertion failure in Buffer::getRange; bufferStates not equal for s1";
    if(s2.p1 !=s2.p2)
        throw "Assertion failure in Buffer::getRange; bufferStates not equal for s1";
    line = s1.line;
    col = s1.col;
    pos = s1.p1;
    return buffer.mid(s1.p1, s2.p1 - s1.p1);
}

QString Buffer::acceptable()
{
    QString ret = buffer.mid(p1, p2 - p1);
    return ret;
}

void Buffer::read(QString string)
{
// todo: this is unoptimized but at least
// doesn't mess up the startOfLine
// which is handled in char read()
// so we use it here:
    for(int i=0; i<string.length(); i++)
        read();
}

void Buffer::reset()
{
    p2 = p1;
    updateStartOfLine();
}

void Buffer::retract(int numChars)
{
    for(int i=0; i<numChars; i++)
    {
        QChar c = buffer[p2-1];
        col --;
        if(c=='\n')
        {
            // We haven't fixed columns yet! Column info will be unreliable
            // whenever retract() is used.
            line--;
        }
        p2--;
    }
    updateStartOfLine();
}

BufferState::BufferState(QString _buffer, int _p1, int _p2, bool _startOfLine, int _col, int _line)
{
    buffer = _buffer;
    p1 = _p1;
    p2 = _p2;
    col = _col;
    line = _line;
    startOfLine = _startOfLine;
}

BufferState::BufferState(const BufferState &other)
{
    this->buffer = other.buffer;
    this->startOfLine = other.startOfLine;
    this->col = other.col;
    this->line = other.line;
    this->p2 = other.p2;
    this->p1 = other.p1;
}

int Buffer::GetColumn()
{
    return col;
}

int Buffer::GetLine()
{
    return line;
}

QString Buffer::remainder()
{
    return buffer.mid(p1);
}

BufferState::BufferState()
{

}
