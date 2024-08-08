; ModuleID = 'not_an_exec.ll'
source_filename = "not_an_exec.cpp"
target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
target triple = "aarch64-unknown-linux-gnu"

; Function Attrs: mustprogress noinline optnone uwtable
define dso_local void @_Z7collatzm(i64 noundef %0) #0 {
  %2 = alloca i64, align 8
  %3 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %4 = load i64, i64* %2, align 8
  store i64 %4, i64* %3, align 8
  br label %5

5:                                                ; preds = %18, %1
  %6 = load i64, i64* %3, align 8
  %7 = icmp ne i64 %6, 1
  br i1 %7, label %8, label %19

8:                                                ; preds = %5
  %9 = load i64, i64* %3, align 8
  %10 = urem i64 %9, 2
  %11 = icmp eq i64 %10, 0
  br i1 %11, label %12, label %15

12:                                               ; preds = %8
  %13 = load i64, i64* %3, align 8
  %14 = call noundef i64 @_ZL7on_evenm(i64 noundef %13)
  store i64 %14, i64* %3, align 8
  br label %18

15:                                               ; preds = %8
  %16 = load i64, i64* %3, align 8
  %17 = call noundef i64 @_ZL6on_oddm(i64 noundef %16)
  store i64 %17, i64* %3, align 8
  br label %18

18:                                               ; preds = %15, %12
  br label %5, !llvm.loop !10

19:                                               ; preds = %5
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define internal noundef i64 @_ZL7on_evenm(i64 noundef %0) #1 {
  %2 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %3 = load i64, i64* %2, align 8
  %4 = udiv i64 %3, 2
  ret i64 %4
}

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define internal noundef i64 @_ZL6on_oddm(i64 noundef %0) #1 {
  %2 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %3 = load i64, i64* %2, align 8
  %4 = mul i64 3, %3
  %5 = add i64 %4, 1
  ret i64 %5
}

attributes #0 = { mustprogress noinline optnone uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon,+outline-atomics,+v8a" }
attributes #1 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon,+outline-atomics,+v8a" }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8}
!llvm.ident = !{!9}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"branch-target-enforcement", i32 0}
!2 = !{i32 1, !"sign-return-address", i32 0}
!3 = !{i32 1, !"sign-return-address-all", i32 0}
!4 = !{i32 1, !"sign-return-address-with-bkey", i32 0}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{i32 7, !"PIE Level", i32 2}
!7 = !{i32 7, !"uwtable", i32 1}
!8 = !{i32 7, !"frame-pointer", i32 1}
!9 = !{!"Ubuntu clang version 14.0.6"}
!10 = distinct !{!10, !11}
!11 = !{!"llvm.loop.mustprogress"}
