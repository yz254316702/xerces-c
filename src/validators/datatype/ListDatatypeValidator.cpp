/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 2001, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Id$
 * $Log$
 * Revision 1.7  2001/10/09 20:56:21  peiyongz
 * inherit from AbstractStringValidator instead of DatatypeValidator to reuse
 * the code.
 *
 * Revision 1.6  2001/10/02 18:59:29  peiyongz
 * Invalid_Facet_Tag to display the tag name
 *
 * Revision 1.5  2001/09/20 13:11:42  knoaman
 * Regx  + misc. fixes
 *
 * Revision 1.4  2001/08/29 19:03:40  peiyongz
 * Bugzilla# 2816:on AIX 4.2, xlC 3 r ev.1, Compilation error on inline method
 *
 * Revision 1.3  2001/08/21 18:42:53  peiyongz
 * Bugzilla# 2816: cleanUp() declared with external linkage and called
 *                          before defined as inline
 *
 * Revision 1.2  2001/08/14 22:11:56  peiyongz
 * new exception message added
 *
 * Revision 1.1  2001/07/11 21:37:17  peiyongz
 * ListDatatypeDTV
 *
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <validators/datatype/ListDatatypeValidator.hpp>
#include <validators/datatype/InvalidDatatypeFacetException.hpp>
#include <validators/datatype/InvalidDatatypeValueException.hpp>
#include <util/NumberFormatException.hpp>

static const int BUF_LEN = 64;
static XMLCh value1[BUF_LEN+1];
static XMLCh value2[BUF_LEN+1];

// ---------------------------------------------------------------------------
//  Constructors and Destructor
// ---------------------------------------------------------------------------
ListDatatypeValidator::ListDatatypeValidator()
:AbstractStringValidator(0, 0, 0, DatatypeValidator::List)
,fContent(0)
{}

ListDatatypeValidator::ListDatatypeValidator(
                          DatatypeValidator*            const baseValidator
                        , RefHashTableOf<KVStringPair>* const facets
                        , RefVectorOf<XMLCh>*           const enums
                        , const int                           finalSet)
:AbstractStringValidator(baseValidator, facets, finalSet, DatatypeValidator::List)
,fContent(0)
{
    //
    // baseValidator shall either 
    // an atomic DTV which servers as itemType, or
    // another ListDTV from which, this ListDTV is derived by restriction.
    // 
    // In either case, it shall be not null
    //
    if (!baseValidator)
        ThrowXML(InvalidDatatypeFacetException, XMLExcepts::FACET_List_Null_baseValidator);

    init(enums);
}

ListDatatypeValidator::~ListDatatypeValidator()
{}

DatatypeValidator* ListDatatypeValidator::newInstance(
                                      RefHashTableOf<KVStringPair>* const facets
                                    , RefVectorOf<XMLCh>*           const enums
                                    , const int                           finalSet)
{
    return (DatatypeValidator*) new ListDatatypeValidator(this, facets, enums, finalSet);
}


int ListDatatypeValidator::compare(const XMLCh* const lValue
                                 , const XMLCh* const rValue)
{
    DatatypeValidator* theItemTypeDTV = getItemTypeDTV();
    RefVectorOf<XMLCh>* lVector = XMLString::tokenizeString(lValue);
    Janitor<RefVectorOf<XMLCh> > janl(lVector);
    RefVectorOf<XMLCh>* rVector = XMLString::tokenizeString(rValue);
    Janitor<RefVectorOf<XMLCh> > janr(rVector);
   
    int lNumberOfTokens = lVector->size();         
    int rNumberOfTokens = rVector->size();         

    if (lNumberOfTokens < rNumberOfTokens)
        return -1; 
    else if (lNumberOfTokens > rNumberOfTokens)
        return 1;
    else 
    { //compare each token   
        for ( int i = 0; i < lNumberOfTokens; i++)
        {
            int returnValue = theItemTypeDTV->compare(lVector->elementAt(i), rVector->elementAt(i));
            if (returnValue != 0) 
                return returnValue; //REVISIT: does it make sense to return -1 or +1..?               
        }
        return 0;
    }
       
}

bool ListDatatypeValidator::isAtomic() const {
    return false;
}

void ListDatatypeValidator::validate( const XMLCh* const content)
{
    setContent(content);
    RefVectorOf<XMLCh>* tokenVector = XMLString::tokenizeString(content);
    Janitor<RefVectorOf<XMLCh> > janName(tokenVector);
    checkContent(tokenVector, false);
}

void ListDatatypeValidator::checkContent( const XMLCh* const content, bool asBase)
{
    setContent(content);
    RefVectorOf<XMLCh>* tokenVector = XMLString::tokenizeString(content);
    Janitor<RefVectorOf<XMLCh> > janName(tokenVector);
    checkContent(tokenVector, asBase);
}

//
// here content is a list of items
//
void ListDatatypeValidator::checkContent( RefVectorOf<XMLCh>* tokenVector, bool asBase)
{
    DatatypeValidator* bv = getBaseValidator();

    if (bv->getType() == DatatypeValidator::List)
        ((ListDatatypeValidator*)bv)->checkContent(tokenVector, true);
    else
    {   // the ultimate itemType DTV
        for (unsigned int i = 0; i < tokenVector->size(); i++)
            bv->validate(tokenVector->elementAt(i));
    }

    int thisFacetsDefined = getFacetsDefined();

    // we check pattern first
    if ( (thisFacetsDefined & DatatypeValidator::FACET_PATTERN ) != 0 )
    {
        // lazy construction
        if (getRegex() == 0) 
        {
            try {
                setRegex(new RegularExpression(getPattern(), SchemaSymbols::fgRegEx_XOption));
            }
            catch (XMLException &e)
            {
                ThrowXML1(InvalidDatatypeValueException, XMLExcepts::RethrowError, e.getMessage());
            }
        }

        //check each and every item in the list   
        for (unsigned int i = 0; i < tokenVector->size(); i++)
        {
            if (getRegex()->matches(tokenVector->elementAt(i)) ==false)
            {
                ThrowXML2(InvalidDatatypeValueException
                    , XMLExcepts::VALUE_NotMatch_Pattern
                    , tokenVector->elementAt(i)
                    , getPattern());
            }

        }
    }

    // if this is a base validator, we only need to check pattern facet
    // all other facet were inherited by the derived type
    if (asBase)
        return;

    unsigned int tokenNumber = tokenVector->size();

    if (((thisFacetsDefined & DatatypeValidator::FACET_MAXLENGTH) != 0) &&
        (tokenNumber > getMaxLength()))
    {
        XMLString::binToText(tokenNumber, value1, BUF_LEN, 10);
        XMLString::binToText(getMaxLength(), value2, BUF_LEN, 10);

        ThrowXML3(InvalidDatatypeValueException
                , XMLExcepts::VALUE_GT_maxLen
                , getContent()
                , value1
                , value2);
    }

    if (((thisFacetsDefined & DatatypeValidator::FACET_MINLENGTH) != 0) &&
        (tokenNumber < getMinLength()))
    {
        XMLString::binToText(tokenNumber, value1, BUF_LEN, 10);
        XMLString::binToText(getMinLength(), value2, BUF_LEN, 10);

        ThrowXML3(InvalidDatatypeValueException
                , XMLExcepts::VALUE_LT_minLen
                , getContent()
                , value1
                , value2);
    }

    if (((thisFacetsDefined & DatatypeValidator::FACET_LENGTH) != 0) &&
        (tokenNumber != AbstractStringValidator::getLength()))
    {
        XMLString::binToText(tokenNumber, value1, BUF_LEN, 10);
        XMLString::binToText(AbstractStringValidator::getLength(), value2, BUF_LEN, 10);

        ThrowXML3(InvalidDatatypeValueException
                , XMLExcepts::VALUE_NE_Len
                , getContent()
                , value1
                , value2);
    }

    if ((thisFacetsDefined & DatatypeValidator::FACET_ENUMERATION) != 0 &&
        (getEnumeration() != 0))
    {
        int i;
        int enumLength = getEnumeration()->size();

        for ( i = 0; i < enumLength; i++)
        {
            //optimization: we do a lexical comparision first
            // this may be faster for string and its derived
            if (XMLString::compareString(getEnumeration()->elementAt(i), getContent()) == 0)
                break; // a match found

            // do a value space check
            // this is needed for decimal (and probably other types 
            // such as datetime related)
            // eg.
            // tokenVector = "1 2 3.0 4" vs enumeration = "1 2 3 4.0"
            //
            if (valueSpaceCheck(tokenVector, getEnumeration()->elementAt(i)))
                break;
        }

        if (i == enumLength)
            ThrowXML1(InvalidDatatypeValueException, XMLExcepts::VALUE_NotIn_Enumeration, getContent());

    } // enumeration

}

bool ListDatatypeValidator::valueSpaceCheck(RefVectorOf<XMLCh>* tokenVector
                                          , const XMLCh* const  enumStr) const
{
    DatatypeValidator* theItemTypeDTV = getItemTypeDTV();
    RefVectorOf<XMLCh>* enumVector = XMLString::tokenizeString(enumStr);
    Janitor<RefVectorOf<XMLCh> > janName(enumVector);

    if (tokenVector->size() != enumVector->size())
        return false;

    for ( unsigned int j = 0; j < tokenVector->size(); j++ )
    {
        if (theItemTypeDTV->compare(tokenVector->elementAt(j), enumVector->elementAt(j)) != 0)
            return false;
    }

    return true;
}

DatatypeValidator* ListDatatypeValidator::getItemTypeDTV() const
{
    DatatypeValidator* bdv = this->getBaseValidator();

    while (bdv->getType() == DatatypeValidator::List)
        bdv = bdv->getBaseValidator();

    return bdv;
}

// ---------------------------------------------------------------------------
//  Utilities
// ---------------------------------------------------------------------------
void ListDatatypeValidator::assignAdditionalFacet( const XMLCh* const key
                                                 , const XMLCh* const)
{
    ThrowXML1(InvalidDatatypeFacetException
            , XMLExcepts::FACET_Invalid_Tag
            , key);
}

void ListDatatypeValidator::inheritAdditionalFacet()
{}

void ListDatatypeValidator::checkAdditionalFacetConstraints() const
{}

void ListDatatypeValidator::checkAdditionalFacet(const XMLCh* const) const
{}

void ListDatatypeValidator::checkValueSpace(const XMLCh* const content)
{}

int ListDatatypeValidator::getLength(const XMLCh* const content) const
{
    RefVectorOf<XMLCh>* tokenVector = XMLString::tokenizeString(content);
    Janitor<RefVectorOf<XMLCh> > janName(tokenVector);

    return tokenVector->size();
}

void ListDatatypeValidator::inspectFacetBase()
{

    //
    // we are pretty sure baseValidator is not null
    //

    if (getBaseValidator()->getType() == DatatypeValidator::List)
    {
        AbstractStringValidator::inspectFacetBase();
    }
    else
    {
        // the first level ListDTV
        // check 4.3.5.c0 must: enumeration values from the value space of base
        if ( ((getFacetsDefined() & DatatypeValidator::FACET_ENUMERATION) != 0) &&
             (getEnumeration() !=0)                                              )
        {
            int i;
            int enumLength = getEnumeration()->size();
            try
            {
                for ( i = 0; i < enumLength; i++)
                {
                    // ask the itemType for a complete check
                    RefVectorOf<XMLCh>* tempList = XMLString::tokenizeString(getEnumeration()->elementAt(i));
                    int tokenNumber = tempList->size();

                    try 
                    {
                        for ( int j = 0; j < tokenNumber; j++)
                            getBaseValidator()->validate(tempList->elementAt(j));
                    }
                    catch (...)
                    {
                        delete tempList;
                        throw;
                    }

                    delete tempList;

                    // enum shall pass this->checkContent() as well.
                    checkContent(getEnumeration()->elementAt(i), false);
                }
            }

            catch ( XMLException& )
            {
                ThrowXML1(InvalidDatatypeFacetException
                        , XMLExcepts::FACET_enum_base
                        , getEnumeration()->elementAt(i));
            }
    
        }

    }

}// End of inspectFacetBase()

/**
  * End of file ListDatatypeValidator.cpp
  */
