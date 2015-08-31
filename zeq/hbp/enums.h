
/* Copyright (c) 2014-2015, Human Brain Project
 *                          Juan Hernando <jhernando@fi.upm.es>
 */

#ifndef ZEQ_HBP_ENUMS_H
#define ZEQ_HBP_ENUMS_H

namespace zeq
{
namespace hbp
{

/** Possible operations for a CellSetBinaryOp event */
enum CellSetBinaryOpType
{
    /** Requests the display of the synaptic pathways from a pre-synaptic
        target to a post-synaptic target. */
    CELLSETOP_SYNAPTIC_PROJECTIONS = 0
};

}
}
#endif
