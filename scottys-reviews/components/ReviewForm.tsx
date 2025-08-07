// components/ReviewForm.tsx
"use client";

import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { z } from "zod";
import { Input } from "@/components/ui/input";
import { Textarea } from "@/components/ui/textarea";
import { Button } from "@/components/ui/button";
import { Select } from "@/components/ui/select";
import { StarRating } from "@/components/StarRating";
import { SearchBar } from "@/components/SearchBar";
import { useState, useEffect, useMemo, useCallback } from "react";
import { toast } from "sonner";

const reviewSchema = z.object({
  courseId: z.string().min(1, "Select a course"),
  rating: z.number().min(1).max(10, "Rating must be between 1 and 5"),
  quarter: z.string().min(3),
  professor: z.string().optional(),
  ta: z.string().optional(),
  text: z.string().min(10, "Review must be at least 10 characters"),
});

export type ReviewInput = z.infer<typeof reviewSchema>;

interface Course {
  courseid: string;
  classname: string;
}

interface Props {
  courses: Course[];
  prefillCourseId?: string | null;
}

export const ReviewForm: React.FC<Props> = ({ courses, prefillCourseId }) => {
  const [rating, setRating] = useState(3);
  const [showSuccess, setShowSuccess] = useState(false);
  const [selectedCourse, setSelectedCourse] = useState<Course | null>(null);

  const {
    register,
    handleSubmit,
    setValue,
    formState: { errors, isSubmitting },
    reset,
  } = useForm<ReviewInput>({
    resolver: zodResolver(reviewSchema),
    defaultValues: {
      courseId: prefillCourseId || "",
      rating: 3,
    },
  });

  // Handle course selection from search bar
  const handleCourseSelect = useCallback((course: Course) => {
    setSelectedCourse(course);
    setValue("courseId", course.courseid);
  }, [setValue]);

  // Clear selected course
  const handleClearCourse = useCallback(() => {
    setSelectedCourse(null);
    setValue("courseId", "");
  }, [setValue]);

  // Set initial course if prefilled
  useEffect(() => {
    if (prefillCourseId) {
      const course = courses.find(c => c.courseid === prefillCourseId);
      if (course) {
        setSelectedCourse(course);
        setValue("courseId", prefillCourseId);
      }
    }
  }, [prefillCourseId, courses, setValue]);

  // 使用 useCallback 缓存提交处理函数
  const onSubmit = useCallback(async (data: ReviewInput) => {
    try {
      const res = await fetch("/api/reviews", {
        method: "POST",
        body: JSON.stringify({
          courseid: data.courseId,
          rating: data.rating,
          quarter: data.quarter,
          professor: data.professor,
          ta: data.ta,
          review: data.text
        }),
      });

      if (res.status === 401) {
        // 未登录，重定向到登录页面
        window.location.href = `/login?callbackUrl=${encodeURIComponent(window.location.pathname)}`;
        return;
      }

      if (res.ok) {
        toast.success("Review submitted!");
        setShowSuccess(true);
        // 提交成功后清空表单
        reset({
          courseId: prefillCourseId || "",
          rating: 3,
        });
        setRating(3);
        if (!prefillCourseId) {
          setSelectedCourse(null);
        }
      } else {
        const error = await res.json();
        toast.error(error.message || "Something went wrong.");
      }
    } catch (error) {
      toast.error("Failed to submit review. Please try again.");
    }
  }, [prefillCourseId, reset]);

  // 使用 useCallback 缓存评分处理函数
  const handleRatingChange = useCallback((val: number) => {
    setRating(val);
    setValue("rating", val);
  }, [setValue]);

  return (
    <>
      {showSuccess && (
        <div className="fixed top-4 right-4 bg-white border border-gray-300 text-gray-800 p-6 rounded-lg shadow-lg z-50 min-w-[300px]">
          <div className="flex justify-between items-center">
            <span className="font-medium">Form submitted successfully</span>
            <button
              onClick={() => setShowSuccess(false)}
              className="text-gray-500 hover:text-gray-700 font-bold text-xl"
              aria-label="Close notification"
            >
              ×
            </button>
          </div>
        </div>
      )}
      
      <form onSubmit={handleSubmit(onSubmit)} className="space-y-4">
        {/* Course Search Bar */}
        <div>
          <label htmlFor="course-search" className="block font-baloo2 font-medium text-md mb-3">Course</label>
          
          {selectedCourse ? (
            // Show selected course
            <div className="flex items-center justify-between bg-gray-50 border rounded-lg p-4">
              <div>
                <div className="font-semibold text-lg">{selectedCourse.courseid}</div>
                <div className="text-gray-600">{selectedCourse.classname}</div>
              </div>
              <button
                type="button"
                onClick={handleClearCourse}
                className="text-red-500 hover:text-red-700 font-bold text-xl"
                aria-label="Clear selection"
              >
                ×
              </button>
            </div>
          ) : (
            // Show search bar
            <div className="space-y-2">
              <SearchBar 
                placeholder="Search for a course to review..."
                onCourseSelect={handleCourseSelect}
              />
              <p className="text-sm text-gray-500">
                Start typing to search for courses by course ID or name
              </p>
            </div>
          )}
          
          {errors.courseId && <p className="text-sm text-red-500 mt-1">{errors.courseId.message}</p>}
        </div>

        {/* Rating */}
        <div>
          <label htmlFor="rating" className="block font-baloo2 font-medium text-md mb-1">Rating</label>
          <StarRating
            rating={rating}
            size={30}
            className="cursor-pointer"
            onClick={handleRatingChange}
          />
          {errors.rating && <p className="text-sm text-red-500">{errors.rating.message}</p>}
        </div>

        {/* Quarter */}
        <div>
          <label htmlFor="quarter" className="block font-baloo2 font-medium text-md mb-1">Quarter and Year Taken</label>
          <Input 
            id="quarter"
            {...register("quarter")} 
            placeholder="e.g., Fall 2023, Winter 2024"
          />
          {errors.quarter && <p className="text-sm text-red-500">{errors.quarter.message}</p>}
        </div>

        {/* Professor */}
        <div>
          <label htmlFor="professor" className="block font-medium text-md mb-1">Professor</label>
          <Input id="professor" {...register("professor")} placeholder="Optional" />
        </div>

        {/* TA */}
        <div>
          <label htmlFor="ta" className="block font-lg text-md mb-1">TA</label>
          <Input id="ta" {...register("ta")} placeholder="Optional"/>
        </div>

        {/* Text */}
        <div>
          <label htmlFor="review-text" className="block font-baloo2 font-lg text-md mb-1">Review</label>
          <Textarea id="review-text" {...register("text")} rows={4} placeholder="What should highlanders know about this class?" />
          {errors.text && <p className="text-sm text-red-500">{errors.text.message}</p>}
        </div>

        <div className="flex justify-end mt-4">
          <Button className="!bg-[#2C1818] hover:!bg-[#2C1818] !text-white" type="submit" disabled={isSubmitting}>
            {isSubmitting ? "Submitting..." : "Submit Review"}
          </Button>
        </div>
      </form>
    </>
  );
};

export default ReviewForm;