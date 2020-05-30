namespace otoge2019 {
  class Schedulable
  {
    public:
      virtual bool isFinished() = 0;
      virtual void scheduledTask() = 0;
  };
} // namespace otoge2019
