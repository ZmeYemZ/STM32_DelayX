#ifndef DELAYX_H_
#define DELAYX_H_

#include <inttypes.h>

#if defined(__cplusplus)
    class CDelayX
    {
    private:
        uint32_t m_uDuration;
        uint32_t m_uTickPrev;
        uint32_t m_uTickNext;
    public:
        CDelayX(uint32_t uDuration, bool bSet = false)
        :m_uDuration(uDuration)
        {
            m_uTickPrev = HAL_GetTick();
            m_uTickNext = m_uTickPrev + m_uDuration;

            if(bSet)
            {
                m_uTickPrev -= m_uDuration;
                m_uTickNext -= m_uDuration;
            }
        }

        bool Huh()
        {
            const uint32_t uTick = HAL_GetTick();

            if(m_uTickPrev < m_uTickNext)
            {
                if(uTick >= m_uTickPrev && uTick < m_uTickNext) return true;
            }
            else
            {
                if(uTick >= m_uTickPrev || uTick < m_uTickNext) return true;
            }

            m_uTickPrev = m_uTickNext;
            m_uTickNext += m_uDuration;
            return false;
        }
    };
#else
    static bool DelayX(uint32_t* puTickPrev, uint32_t uDuration)
    {
        const uint32_t uTick = HAL_GetTick();
        const uint32_t uTickPrev = *puTickPrev;
        const uint32_t uTickNext = uTickPrev + uDuration;

        if(uTickPrev < uTickNext)
        {
            if(uTick >= uTickPrev && uTick < uTickNext) return true;
        }
        else
        {
            if(uTick >= uTickPrev || uTick < uTickNext) return true;
        }

        *puTickPrev = uTickNext;
        return false;
    }
#endif

#endif /* DELAYX_H_ */
