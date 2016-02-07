#ifndef __EINK_H__
#define __EINK_H__

#define EINK_OS_VERSION_MAJOR      0
#define EINK_OS_VERSION_MINOR      1

#define serialDriver                  (&SD3)
#define stream_driver                 ((BaseSequentialStream *)serialDriver)
extern void *stream;

#endif /* __EINK_H__ */
