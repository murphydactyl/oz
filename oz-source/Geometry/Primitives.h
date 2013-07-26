/*
 * CREATE GENERIC GEOMETRY
 */

namespace geom {

  class Geometry;

  Geometry* makeBox(float width = 1.0f, float height=0.5f, float depth=2.0f);
  Geometry* makeQuad(float unit=1.0f);
}
