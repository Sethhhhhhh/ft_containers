#ifndef __UTILS_HPP__
# define __UTILS_HPP__

/* https://stackoverflow.com/questions/44517556/how-to-define-our-own-nullptr-in-c98/44517878 */
const class nullptr_t {             /* this is a const object...     */

    public:
        template<class T>           /* convertible to any type       */
        operator T*() const {       /* of null non-member            */
            return 0;               /* pointer...                    */
        }

        template<class C, class T>  /* or any type of null           */
        operator T C::*() const {   /* member pointer...             */
            return 0;
        }

    private:
        void operator&() const;     /* Can't take address of nullptr */

} u_nullptr = {};

#endif