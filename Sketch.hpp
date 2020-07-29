#ifndef _SKETCH_
#define _SKETCH_

//======== parameter ===========
#define ListLength 15

class Sketch
{
private:
    /* data */
public:
    Sketch(/* args */);
    ~Sketch();
};

class SketchList : public Sketch
{
private:
  Sketch _sketchL[ListLength];

public:
  SketchList(/* argLists */);
  ~SketchList();
  void updateSketchList();
  Sketch* getSketchList(); 

};


#endif