/*
  Copyright (c) 2016 DataStax, Inc.

  This software can be used solely with DataStax Enterprise. Please consult the
  license at http://www.datastax.com/terms/datastax-dse-driver-license-terms
*/

#ifndef __DSE_EXTERNAL_TYPES_HPP_INCLUDED__
#define __DSE_EXTERNAL_TYPES_HPP_INCLUDED__

#include "dse.h"

#include "graph.hpp"
#include "line_string.hpp"
#include "polygon.hpp"

// This abstraction allows us to separate internal types from the
// external opaque pointers that we expose.
template <typename In, typename Ex>
struct External : public In {
  In* from() { return static_cast<In*>(this); }
  const In* from() const { return static_cast<const In*>(this); }
  static Ex* to(In* in) { return static_cast<Ex*>(in); }
  static const Ex* to(const In* in) { return static_cast<const Ex*>(in); }
};

#define EXTERNAL_TYPE(InternalType, ExternalType)                        \
  struct ExternalType##_ : public External<InternalType, ExternalType> { \
    private:                                                             \
      ~ExternalType##_() { }                                             \
  }

extern "C" {

EXTERNAL_TYPE(dse::GraphOptions, DseGraphOptions);
EXTERNAL_TYPE(dse::GraphStatement, DseGraphStatement);
EXTERNAL_TYPE(dse::GraphArray, DseGraphArray);
EXTERNAL_TYPE(dse::GraphObject, DseGraphObject);
EXTERNAL_TYPE(dse::GraphResultSet, DseGraphResultSet);
EXTERNAL_TYPE(dse::GraphResult, DseGraphResult);
EXTERNAL_TYPE(dse::LineSegment, DseLineString);
EXTERNAL_TYPE(dse::LineSegmentIterator, DseLineStringIterator);
EXTERNAL_TYPE(dse::Polygon, DsePolygon);
EXTERNAL_TYPE(dse::PolygonIterator, DsePolygonIterator);

}

#undef EXTERNAL_TYPE

#endif
