#ifndef BUBBLE_RING_HPP
#define BUBBLE_RING_HPP

// A circular buffer for bubbles.
// Used to cache the last N recently pushed bubbles.

#include <cstdint>
#include <utility>
#include <array>
#include <limits>
#include <variant>

namespace Awax86{

enum class BubbleType: std::uint8_t{Single, Double, Unknown};

template<std::size_t N>
class BubbleRing{
  struct BubbleRing_error{};
  struct DoubleBubble{};
  using value_type = std::uint8_t;
  //using stack_entry_t = std::pair<BubbleType, value_type>;
  //using stack_entry_t = value_type;
  using stack_entry_t = std::pair<BubbleType, std::variant<DoubleBubble, value_type>>;
  public:
    //---------------------------------------------------------------//
    // Lifetime
    //---------------------------------------------------------------//

    explicit BubbleRing():
      m_empty{true},
      m_index{0},
      m_buffer{}
    {
      for(auto& [type, val] : m_buffer){
        type = BubbleType::Unknown;
        val = std::uint8_t{0};
      }
    }

    //---------------------------------------------------------------//
    // Modifiers:
    //    These function contain standard LRU cache instructions
    //---------------------------------------------------------------//

    void Push(const stack_entry_t value){
      if(m_empty){
        m_buffer[m_index] = value;
        m_empty = false;
      }
      else{
        m_index++;
        m_index %= N;
        m_buffer[m_index] = value;
      }
    }

    //---------------------------------------------------------------//
    // Readers:
    //    Functions which aids in reading the state of the cache.
    //    Mostly consists of querying the existing data.
    //---------------------------------------------------------------//

    [[nodiscard]] std::size_t GetIndex() const { return m_index; }

    [[nodiscard]] bool Contains(const value_type& val) const{ 
      for(auto& i: m_buffer){
        if(val == i) return true;
      }
      return false;
    }

    [[nodiscard]] bool AllSingles() const{
      std::size_t count = 0;
      for(auto& [type, value] : m_buffer){
        if(type == BubbleType::Single){
          count++;
        }
      }
      return count == N ? true : false;
    }

    [[nodiscard]] bool AllEquals() const{
      // we make the assumption that all of the entries are single bubble type
      for(std::size_t i = 0; i < m_buffer.size(); i++){
        stack_entry_t previous;
        if(i == 0){
          previous = m_buffer[i];
        }
        else{
          stack_entry_t current = m_buffer[i];
          const value_type* pprevious = std::get_if<value_type>(&previous.second);
          const value_type* pcurrent = std::get_if<value_type>(&current.second);
          if((pprevious && pcurrent) && !(*pprevious == *pcurrent)){
            return false;
          }
        }
      }
      return true;
    }

    //---------------------------------------------------------------//
    // Operator overloads:
    //    should return value_types
    //---------------------------------------------------------------//

    [[nodiscard]] value_type operator[](std::size_t index) const{
      if(index >= N){
        throw BubbleRing_error{};
      }
      stack_entry_t var = m_buffer[index];
      if(const value_type* p = std::get_if<value_type>(&var.second)){
        return *p;
      }
      else{
        throw BubbleRing_error{};

      }
    }

  private:
    bool m_empty;
    std::size_t m_index;
    std::array<stack_entry_t, N> m_buffer;
};

} // namespace Awax86

#endif
