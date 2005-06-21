/*
 * Copyright 2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Id$
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/identity/XPathMatcherStack.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  XPathMatherStack: Constructors and Destructor
// ---------------------------------------------------------------------------
XPathMatcherStack::XPathMatcherStack(MemoryManager* const manager)
    : fMatchersCount(0)
    , fContextStack(new (manager) ValueStackOf<int>(8, manager))
    , fMatchers(0)
{
    try {
        fMatchers = new (manager) RefVectorOf<XPathMatcher>(8, true, manager);
    }
    catch(const OutOfMemoryException&)
    {
        throw;
    }
    catch(...) {

        delete fContextStack;
        throw;
    }
}

XPathMatcherStack::~XPathMatcherStack() {

    delete fContextStack;
    delete fMatchers;
}

// ---------------------------------------------------------------------------
//  XPathMatherStack: Clear methods
// ---------------------------------------------------------------------------
void XPathMatcherStack::clear() {

    fContextStack->removeAllElements();
    fMatchers->removeAllElements();
    fMatchersCount = 0;
}

XERCES_CPP_NAMESPACE_END

/**
  * End of file XPathMatcherStack.cpp
  */
